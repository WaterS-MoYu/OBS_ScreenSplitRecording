/*
Plugin Name
Copyright (C) <Year> <Developer> <Email Address>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <https://www.gnu.org/licenses/>
*/

#include <obs-module.h>
#include <plugin-support.h>
#include <util/platform.h>
#include <util/dstr.h>
#include <obs-frontend-api.h>
#include <windows.h>

#include <QDialog>
#include <properties-view.hpp>

#define PROP_SOURCE "SSR_source_name"
#define PROP_SCREENPOSID "SSR_screen_pos_id"
#define PROP_CAMID "SSR_cam_id"
#define PROP_TXTFILE "SSR_txt_file"

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "zh-CN")

static bool is_recording = false;
static obs_hotkey_id hotkey_id_recording = OBS_INVALID_HOTKEY_ID;

static char *source_name = NULL;
static char *file_postfix = NULL;
static char *name_source_file = NULL;


static void rename_recording_file(const char *src_path, const char *base_name)
{
    char drive[_MAX_DRIVE], dir[_MAX_DIR], ext[_MAX_EXT];
    _splitpath_s(src_path, drive, sizeof(drive), dir, sizeof(dir),
                 NULL, 0, ext, sizeof(ext));

    char folder[MAX_PATH];
    snprintf(folder, sizeof(folder), "%s%s", drive, dir);

    int counter = 0;
    char new_path[MAX_PATH];
    while (true) {
        if (counter == 0) {
            snprintf(new_path, sizeof(new_path), "%s%s%s", folder, base_name, ext);
        } else {
            snprintf(new_path, sizeof(new_path), "%s%s_%d%s", folder, base_name, counter, ext);
        }

        if (!os_file_exists(new_path))
            break;

        counter++;
    }

    if (os_rename(src_path, new_path) == 0) {
        obs_log(LOG_INFO, "[obs-screen-split-recording] Recording %s renamed to: %s",src_path, new_path);
    } else {
        obs_log(LOG_WARNING, "[obs-screen-split-recording] Failed to rename recording %s to: %s",src_path, new_path);
    }
}

static void recording_stopped_callback(enum obs_frontend_event event, void *)
{
    if (event == OBS_FRONTEND_EVENT_RECORDING_STOPPED) {
        is_recording = false;

        const char *recording_path = obs_frontend_get_last_recording();
        if (!recording_path) return;

        char *new_name = NULL;

        FILE *fp = fopen(name_source_file, "r");
        if (fp) {
            fseek(fp, -256, SEEK_END);
            char line[256];
            while (fgets(line, sizeof(line), fp)) {
                // do nothing; just read to the end
            }
            fclose(fp);

            strtok(line, "\r\n");
            size_t len = strlen(line) + strlen(file_postfix) + 32;
            new_name = (char *)malloc(len);
            snprintf(new_name, len, "%s_%s", line, file_postfix);
        } else {
            obs_log(LOG_WARNING, "[obs-screen-split-recording] name source file not found: %s", name_source_file);
            return;
        }

        rename_recording_file(recording_path, new_name);
        free(new_name);
    }
}

static void switch_recording(void *data, obs_hotkey_id id, obs_hotkey_t *hotkey, bool pressed)
{
    if (!pressed) return;

    if (is_recording) {
        obs_frontend_recording_stop();
        is_recording = false;
    } else {
        obs_frontend_recording_start();
        is_recording = true;
    }
}

bool obs_module_load(void)
{
	obs_frontend_add_event_callback(recording_stopped_callback, nullptr);
    hotkey_id_recording = obs_hotkey_register_frontend("ID_Recording", "Switch Recording State", switch_recording, nullptr);

	char *setting_file_path = obs_module_file("obs_ssr_config/settings.json");
    obs_log(LOG_INFO, "[obs-screen-split-recording] setting file : %s", setting_file_path);

	obs_data_t *setting_json_data = obs_data_create_from_json_file(setting_file_path);
	obs_data_array_t *Recording_hotkey = obs_data_get_array(setting_json_data, "ID_Recording");
	obs_hotkey_load(hotkey_id_recording, Recording_hotkey);

    const char *CamID = obs_data_get_string(setting_json_data, "CamID");
    file_postfix = bstrdup(CamID);
    obs_log(LOG_WARNING, "[obs-screen-split-recording] cam id : %s", file_postfix);
    
    const char *NameSourceFile = obs_data_get_string(setting_json_data, "NameSourceFile");
    name_source_file = bstrdup(NameSourceFile);
    obs_log(LOG_WARNING, "[obs-screen-split-recording] name source file : %s", name_source_file);

	obs_data_release(setting_json_data);
	obs_data_array_release(Recording_hotkey);
	bfree(setting_file_path);

    /*auto main_window = static_cast<QMainWindow *>(obs_frontend_get_main_window());

	if (main_window) {
		auto menu_action = static_cast<QAction *>(
			obs_frontend_add_tools_menu_qaction(obs_module_text("obs-screen-split-recording.SettingsMenu")));

		obs_frontend_push_ui_translation(obs_module_get_string);
		output_settings = new OutputSettings(main_window);
		obs_frontend_pop_ui_translation();

		auto menu_cb = [] {
			output_settings->toggleShowHide();
		};
		menu_action->connect(menu_action, &QAction::triggered, menu_cb);

		obs_frontend_add_event_callback(
			[](enum obs_frontend_event event, void *) {
				if (event == OBS_FRONTEND_EVENT_FINISHED_LOADING) {
					main_output_init();
					preview_output_init();
				} else if (event == OBS_FRONTEND_EVENT_EXIT) {
					// Unknown why putting this in obs_module_unload causes a crash when closing OBS
					main_output_deinit();
					preview_output_deinit();
				} else if (event == OBS_FRONTEND_EVENT_PROFILE_CHANGING) {
					main_output_deinit();
				} else if (event == OBS_FRONTEND_EVENT_PROFILE_CHANGED) {
					main_output_init();
				}
			},
			nullptr);
	}*/

	obs_log(LOG_INFO, "plugin %s loaded successfully (version %s)", PLUGIN_NAME, PLUGIN_VERSION);
	return true;
}

void obs_module_unload(void)
{
	if (source_name) bfree(source_name);
    if (file_postfix) bfree(file_postfix);
	obs_log(LOG_INFO, "plugin unloaded");
}

/*
{
    obs_properties_t *props = obs_properties_create();

    obs_property_t *source_list = obs_properties_add_list(
        props, PROP_SOURCE, obs_module_text("obs-screen-split-recording.RecordingSource"),
        OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);

    obs_source_t **sources = obs_enum_sources();
    if (sources) {
        for (size_t i = 0; sources[i]; ++i) {
            const char *name = obs_source_get_name(sources[i]);
            obs_property_list_add_string(source_list, name, name);
        }
        bfree(sources);
    }

	obs_property_t *ScrPosID_list = obs_properties_add_list(
        props, PROP_SCREENPOSID, obs_module_text("obs-screen-split-recording.ScreenPosID"),
        OBS_COMBO_TYPE_LIST, OBS_COMBO_FORMAT_STRING);

    const char *ScrPosIds[] = {"1x1", "2x2UpLeft", "2x2UpRight", "2x2UpLeft", "2x2UpLeft"};
    for (size_t i = 0; i < sizeof(ScrPosIds)/sizeof(ScrPosIds[0]); ++i)
	{
        obs_property_list_add_string(ScrPosID_list, ScrPosIds[i], ScrPosIds[i]);
	}

    obs_property_t *CamId_list = obs_properties_add_list(
        props, PROP_CAMID, obs_module_text("obs-screen-split-recording.CamID"),
        OBS_COMBO_TYPE_EDITABLE, OBS_COMBO_FORMAT_STRING);

    const char *CamIds[] = {"CamA", "CamB", "CamC", "CamD", "CamE"};
    for (size_t i = 0; i < sizeof(CamIds)/sizeof(CamIds[0]); ++i)
	{
        obs_property_list_add_string(CamId_list, CamIds[i], CamIds[i]);
	}

	obs_property_t *FilePath = obs_properties_add_path(
		props, PROP_TXTFILE, obs_module_text("obs-screen-split-recording.NameSourceFile"),
		OBS_PATH_FILE, obs_module_text("obs-screen-split-recording.TextFileFilter"), NULL);
	obs_property_set_long_description(
		FilePath, obs_module_text("obs-screen-split-recording.TextFile.Encoding"));

    return props;
}*/