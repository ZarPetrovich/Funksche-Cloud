#include <arduino.h>
#include <esp_dmx.h>


int RX_Pin = 16;
dmx_port_t dmxPort = 1;
byte dmxdata [7];
QueueHandle_t queue;
bool dmxIsConnected = false;

void setup() {
  Serial.begin(115200);
  dmx_config_t dmxConfig = DMX_DEFAULT_CONFIG;
  dmx_param_config(dmxPort, &dmxConfig);
  dmx_set_pin(dmxPort, DMX_PIN_NO_CHANGE, RX_Pin, DMX_PIN_NO_CHANGE);
  int queueSize = 1;
  int interruptPriority = 1;
  dmx_driver_install(dmxPort, DMX_MAX_PACKET_SIZE, queueSize, &queue,
                     interruptPriority);

}


void loop () {

dmx_event_t packet;

if (xQueueReceive(queue, &packet, DMX_PACKET_TIMEOUT_TICK)) {

  if (packet.status == DMX_OK) 
  dmx_read_packet(dmxPort, dmxdata, packet.size);
  }

}
