#include "../SDK/foobar2000.h"
#include "SoundTouch/SoundTouch.h"
#include "dsp_guids.h"
#define MYVERSION "0.20"

static pfc::string_formatter g_get_component_about()
{
	pfc::string_formatter about;
	about << "A special effect DSP for foobar2000 1.3 ->\n";
	about << "Written by mudlord.\n";
	about << "Portions by Jon Watte, Jezar Wakefield, Chris Moeller, Gian-Carlo Pascutto.\n";
	about << "Using SoundTouch library version "<< SOUNDTOUCH_VERSION << "\n";
	about << "SoundTouch (c) Olli Parviainen\n";
	return about;
}

/*

class dsp_cfg_mainthread : public main_thread_callback {
	dsp_preset_impl new_preset;
	dsp_preset_impl old_preset;

public:
	dsp_cfg_mainthread(
		const dsp_preset & n, const dsp_preset & p) :
		new_preset(n), old_preset(p) {	}

	~dsp_cfg_mainthread()
	{
	}

	void callback_run() override
	{
		// Find and replace
		dsp_chain_config_impl chain;
		static_api_ptr_t<dsp_config_manager> manager;
		manager->get_core_settings(chain);
		for (int i = 0, j = chain.get_count(); i < j; i++)
		{
			if (chain.get_item(i) == old_preset)
			{
				chain.replace_item(new_preset, i);
				manager->set_core_settings(chain);
				break;
			}
		}
	}
};

static pfc::list_t<dsp_preset_impl> opened_configs;

class dsp_menu_callback : public dsp_preset_edit_callback {
	dsp_preset_impl m_data;
public:
	dsp_menu_callback(const dsp_preset & p_data) : m_data(p_data)
	{
		opened_configs.add_item(m_data);
		dsp_entry::g_show_config_popup_v2(p_data, core_api::get_main_window(), *this);
		opened_configs.remove_item(m_data);
	}

	~dsp_menu_callback()
	{
	}

	void on_preset_changed(const dsp_preset & p_data)
	{
		// After callback has been processed
		opened_configs.replace_item(opened_configs.find_item(m_data), p_data);
		service_ptr_t<dsp_cfg_mainthread> ptr = new service_impl_t<dsp_cfg_mainthread>(p_data, m_data);
		//service_impl_t<dsp_cfg_mainthread>* cb = new service_impl_t<dsp_cfg_mainthread>();
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(ptr);
		m_data.copy(p_data);
	}

	static bool is_cfg_opened(const dsp_preset & p_data)
	{
		return opened_configs.find_item(p_data) < INFINITE;
	}
};
*/
// {35FDAA75-AAC9-4EFE-9091-D12E7398EF4A}
static const GUID g_mainmenu_group_id =
{ 0x35fdaa75, 0xaac9, 0x4efe,{ 0x90, 0x91, 0xd1, 0x2e, 0x73, 0x98, 0xef, 0x4a } };
static mainmenu_group_popup_factory g_mainmenu_group(g_mainmenu_group_id,
	mainmenu_groups::view, mainmenu_commands::sort_priority_base, "Effect DSP");

class mainmenu_commands_sample : public mainmenu_commands {
	dsp_chain_config_impl chain;

public:
	void execute(t_uint32 p_index, service_ptr_t<service_base> p_callback) {
		get_command_count(); // Gotta refresh first
		switch (p_index)
		{
		case 0:
			::PitchMainMenuWindow();
			break;
		}
	}

	static const int cmd_max = 32;

	t_uint32 get_command_count()
	{
		return 1;
	}

	GUID get_parent() { return g_mainmenu_group_id; }

	GUID get_command(t_uint32 p_index) {
		GUID base =
		{ 0xf53517a1, 0x615e, 0x46da,{ 0xb1, 0x7, 0xa5, 0x31, 0x99, 0xb8, 0x6b, 0xc9 } };
		base.Data3 = base.Data3 + p_index;
		return base;
	}

	void get_name(t_uint32 p_index, pfc::string_base & p_out) {
		p_out.reset();
		p_out += "Pitch Shift DSP config";
	}

	bool get_description(t_uint32 p_index, pfc::string_base & p_out) {

		pfc::string8 text;
		p_out.reset();
		if (p_index == 0)p_out = "Opens Pitch Shift DSP window.";
		return true;
	}

	bool get_display(
		t_uint32 p_index,
		pfc::string_base & p_text,
		t_uint32 & p_flags)
	{
		if (p_index == 0) p_text = "Pitch Shift";
		return true;
	}
};
static mainmenu_commands_factory_t < mainmenu_commands_sample >g_mainmenu_commands_sample_factory;


/*
class dsp_cfg_mainthread : public main_thread_callback {
	dsp_preset_impl new_preset;
	dsp_preset_impl old_preset;

public:
	dsp_cfg_mainthread(
		const dsp_preset & n, const dsp_preset & p) :
		new_preset(n), old_preset(p)	{	}

	~dsp_cfg_mainthread()
	{
	}

	void callback_run() override
	{
		// Find and replace
		dsp_chain_config_impl chain;
		static_api_ptr_t<dsp_config_manager> manager;
		manager->get_core_settings(chain);
		for (int i = 0, j = chain.get_count(); i < j; i++)
		{
			if (chain.get_item(i) == old_preset)
			{
				chain.replace_item(new_preset, i);
				manager->set_core_settings(chain);
				break;
			}
		}
	}
};

static pfc::list_t<dsp_preset_impl> opened_configs;

class dsp_menu_callback : public dsp_preset_edit_callback {
	dsp_preset_impl m_data;
public:
	dsp_menu_callback(const dsp_preset & p_data) : m_data(p_data)
	{
		opened_configs.add_item(m_data);
		dsp_entry::g_show_config_popup_v2(p_data, core_api::get_main_window(), *this);
		opened_configs.remove_item(m_data);
	}

	~dsp_menu_callback()
	{
	}

	void on_preset_changed(const dsp_preset & p_data)
	{
		// After callback has been processed
		opened_configs.replace_item(opened_configs.find_item(m_data), p_data);
		service_ptr_t<dsp_cfg_mainthread> ptr = new service_impl_t<dsp_cfg_mainthread>(p_data, m_data);
		//service_impl_t<dsp_cfg_mainthread>* cb = new service_impl_t<dsp_cfg_mainthread>();
		static_api_ptr_t<main_thread_callback_manager>()->add_callback(ptr);
		m_data.copy(p_data);
	}

	static bool is_cfg_opened(const dsp_preset & p_data)
	{
		return opened_configs.find_item(p_data) < INFINITE;
	}
};

// {35FDAA75-AAC9-4EFE-9091-D12E7398EF4A}
static const GUID g_mainmenu_group_id =
{ 0x35fdaa75, 0xaac9, 0x4efe, { 0x90, 0x91, 0xd1, 0x2e, 0x73, 0x98, 0xef, 0x4a } };
static mainmenu_group_popup_factory g_mainmenu_group(g_mainmenu_group_id,
	mainmenu_groups::view, mainmenu_commands::sort_priority_base, "DSP");

class mainmenu_commands_sample : public mainmenu_commands {
	dsp_chain_config_impl chain;

public:
	void execute(t_uint32 p_index, service_ptr_t<service_base> p_callback) {
		get_command_count(); // Gotta refresh first


		if (p_index == 0)
		{
			service_enum_t<preferences_page> e;
			service_ptr_t<preferences_page> ptr;
			while (e.next(ptr)) {
				if (0 == strcmp("DSP Manager", ptr->get_name())) {
					static_api_ptr_t<ui_control>()->show_preferences(ptr->get_guid());
					break;
				}
			}
			return;
		}

		if (p_index >= chain.get_count()+1 ||
			!dsp_entry::g_have_config_popup(
			chain.get_item(p_index-1).get_owner()) ||
			dsp_menu_callback::is_cfg_opened(chain.get_item(p_index-1)))
		{
			return;
		}
		else
		{
			dsp_preset_impl * preset = static_cast<dsp_preset_impl*>(new dsp_preset_impl(chain.get_item(p_index - 1)));
			dsp_menu_callback dmc(*preset);
			delete preset;
		}
	}

	static const int cmd_max = 32;

	t_uint32 get_command_count()
	{
		chain.remove_all();
		static_api_ptr_t<dsp_config_manager> manager;
		manager->get_core_settings(chain);
		return cmd_max;
	}

	GUID get_parent() { return g_mainmenu_group_id; }

	GUID get_command(t_uint32 p_index) {
		GUID base =
		{ 0xf53517a1, 0x615e, 0x46da, { 0xb1, 0x7, 0xa5, 0x31, 0x99, 0xb8, 0x6b, 0xc9 } };
		base.Data3 = base.Data3 + p_index;
		return base;
	}

	void get_name(t_uint32 p_index, pfc::string_base & p_out) {
		p_out.reset();
		pfc::string8 text;
		if (p_index > 0)
		{
			bool b = dsp_menu_callback::is_cfg_opened(chain.get_item(p_index - 1));
			if (dsp_entry::g_have_config_popup(
				chain.get_item(p_index - 1).get_owner()))
				dsp_entry::g_name_from_guid(text,
					chain.get_item(p_index - 1).get_owner());
			p_out += text;
			p_out += " config";
		}
	}

	bool get_description(t_uint32 p_index, pfc::string_base & p_out) {
		
		pfc::string8 text;
		p_out.reset();
		if (p_index > 0)
		{
			bool b = dsp_menu_callback::is_cfg_opened(chain.get_item(p_index - 1));
			if (dsp_entry::g_have_config_popup(
				chain.get_item(p_index - 1).get_owner()))
			dsp_entry::g_name_from_guid(text,
				chain.get_item(p_index - 1).get_owner());
			p_out += "Opens ";
			p_out += text;
			p_out +=" configuration window";
		}
		if (p_index == 0)p_out = "Opens DSP configuration manager window.";
		return true;
	}

	bool get_display(
		t_uint32 p_index,
		pfc::string_base & p_text,
		t_uint32 & p_flags)
	{
		if (p_index == 0) p_text = "DSP configuration manager";
		if (p_index >= chain.get_count() +1) return false;

		if (p_index > 0)
		{
			bool b = dsp_menu_callback::is_cfg_opened(chain.get_item(p_index-1));
			if (!dsp_entry::g_have_config_popup(
				chain.get_item(p_index-1).get_owner()))
			{
				p_flags |= mainmenu_commands::flag_disabled;
			}
			if (dsp_menu_callback::is_cfg_opened(chain.get_item(p_index-1)))
			{
				p_flags |= mainmenu_commands::flag_disabled |
					mainmenu_commands::flag_checked;
			}
			dsp_entry::g_name_from_guid(p_text,
				chain.get_item(p_index-1).get_owner());
		}
		return true;
	}
};
*/

//static mainmenu_commands_factory_t < mainmenu_commands_sample >g_mainmenu_commands_sample_factory;
DECLARE_COMPONENT_VERSION_COPY(
"Effect DSP",
MYVERSION,
g_get_component_about()
);
VALIDATE_COMPONENT_FILENAME("foo_dsp_effect.dll");