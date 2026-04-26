#include "commands.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
// I wrote the first few functions than used it as a template for the AI for the
// rest. Not paticularly interesting.
int sv_accept_transfers(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "accept-transfers");
  strcat(command, value);
  return sv_Console(command);
}

int sv_allow_flight(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "allow-flight");
  strcat(command, value);
  return sv_Console(command);
}

int sv_broadcast_console_to_ops(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "broadcast-console-to-ops");
  strcat(command, value);
  return sv_Console(command);
}

int sv_broadcast_rcon_to_ops(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "broadcast-rcon-to-ops");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enable_command_block(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enable-command-block");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enable_jmx_monitoring(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enable-jmx-monitoring");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enable_query(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enable-query");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enable_rcon(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enable-rcon");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enable_status(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enable-status");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enforce_secure_profile(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enforce-secure-profile");
  strcat(command, value);
  return sv_Console(command);
}

int sv_enforce_whitelist(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "enforce-whitelist");
  strcat(command, value);
  return sv_Console(command);
}

int sv_force_gamemode(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "force-gamemode");
  strcat(command, value);
  return sv_Console(command);
}

int sv_hardcore(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "hardcore");
  strcat(command, value);
  return sv_Console(command);
}

int sv_hide_online_players(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "hide-online-players");
  strcat(command, value);
  return sv_Console(command);
}

int sv_log_ips(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "log-ips");
  strcat(command, value);
  return sv_Console(command);
}

int sv_prevent_proxy_connections(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "prevent-proxy-connections");
  strcat(command, value);
  return sv_Console(command);
}

int sv_require_resource_pack(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "require-resource-pack");
  strcat(command, value);
  return sv_Console(command);
}

int sv_sync_chunk_writes(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "sync-chunk-writes");
  strcat(command, value);
  return sv_Console(command);
}

int sv_use_native_transport(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "use-native-transport");
  strcat(command, value);
  return sv_Console(command);
}

int sv_white_list(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "white-list");
  strcat(command, value);
  return sv_Console(command);
}

int sv_online_mode(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "online-mode");
  strcat(command, value);
  return sv_Console(command);
}

int sv_generate_structures(bool x) {
  char *value = (x) ? " true" : " false";
  char command[64] = "";
  strcat(command, "generate-structures");
  strcat(command, value);
  return sv_Console(command);
}

int sv_entity_broadcast_range_percentage(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "entity-broadcast-range-percentage");
  strcat(command, value);
  return sv_Console(command);
}

int sv_function_permission_level(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "function-permission-level");
  strcat(command, value);
  return sv_Console(command);
}

int sv_max_chained_neighbor_updates(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "max-chained-neighbor-updates");
  strcat(command, value);
  return sv_Console(command);
}

int sv_max_players(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "max-players");
  strcat(command, value);
  return sv_Console(command);
}

int sv_max_tick_time(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "max-tick-time");
  strcat(command, value);
  return sv_Console(command);
}

int sv_max_world_size(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "max-world-size");
  strcat(command, value);
  return sv_Console(command);
}

int sv_network_compression_threshold(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "network-compression-threshold");
  strcat(command, value);
  return sv_Console(command);
}

int sv_op_permission_level(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "op-permission-level");
  strcat(command, value);
  return sv_Console(command);
}

int sv_player_idle_timeout(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "player-idle-timeout");
  strcat(command, value);
  return sv_Console(command);
}

int sv_query_port(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "query.port");
  strcat(command, value);
  return sv_Console(command);
}

int sv_rate_limit(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "rate-limit");
  strcat(command, value);
  return sv_Console(command);
}

int sv_rcon_port(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "rcon.port");
  strcat(command, value);
  return sv_Console(command);
}

int sv_server_port(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "server-port");
  strcat(command, value);
  return sv_Console(command);
}

int sv_simulation_distance(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "simulation-distance");
  strcat(command, value);
  return sv_Console(command);
}

int sv_spawn_protection(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "spawn-protection");
  strcat(command, value);
  return sv_Console(command);
}

int sv_view_distance(int x) {
  char value[32];
  sprintf(value, " %d", x);
  char command[64] = "";
  strcat(command, "view-distance");
  strcat(command, value);
  return sv_Console(command);
}

int sv_difficulty(const char *x) {
  char command[256] = "";
  strcat(command, "difficulty ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_gamemode(const char *x) {
  char command[256] = "";
  strcat(command, "gamemode ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_generator_settings(const char *x) {
  char command[256] = "";
  strcat(command, "generator-settings ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_initial_disabled_packs(const char *x) {
  char command[256] = "";
  strcat(command, "initial-disabled-packs ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_initial_enabled_packs(const char *x) {
  char command[256] = "";
  strcat(command, "initial-enabled-packs ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_level_name(const char *x) {
  char command[256] = "";
  strcat(command, "level-name ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_level_seed(const char *x) {
  char command[256] = "";
  strcat(command, "level-seed ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_level_type(const char *x) {
  char command[256] = "";
  strcat(command, "level-type ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_motd(const char *x) {
  char command[256] = "";
  strcat(command, "motd ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_rcon_password(const char *x) {
  char command[256] = "";
  strcat(command, "rcon.password ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_resource_pack(const char *x) {
  char command[256] = "";
  strcat(command, "resource-pack ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_resource_pack_id(const char *x) {
  char command[256] = "";
  strcat(command, "resource-pack-id ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_resource_pack_prompt(const char *x) {
  char command[256] = "";
  strcat(command, "resource-pack-prompt ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_resource_pack_sha1(const char *x) {
  char command[256] = "";
  strcat(command, "resource-pack-sha1 ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_server_ip(const char *x) {
  char command[256] = "";
  strcat(command, "server-ip ");
  strcat(command, x);
  return sv_Console(command);
}

int sv_text_filtering_config(const char *x) {
  char command[256] = "";
  strcat(command, "text-filtering-config ");
  strcat(command, x);
  return sv_Console(command);
}
