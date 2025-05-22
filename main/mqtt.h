#pragma once

// void mqtt_init(void);
void mqtt_init(const char *serverURI, const char *token);

void mqtt_publish(const char *topic, const char *json_payload);
