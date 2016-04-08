-- Lua test
config = tgs.config_init()
tgs.config_read(config, "example.json");
tgs.config_save(config, "example.json");
tgs.config_quit(config)
