#pragma once

/* Handle SIGINT ("Ctrl-C") signals by gracefully stopping the
   server */
static void
sigint_handler (int signal_number);


void* start_thrift_server (void* args);
