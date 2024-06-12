/*
 * Copyright/Licensing information.
 */

/* inclusion guard */
#pragma once

#include <glib-object.h>
#include <thrift/c_glib/thrift.h>

#include "gen-c_glib/seafile.h"

/*
 * Potentially, include other headers on which this header depends.
 */
G_BEGIN_DECLS

/*
 * Type declaration.
 */
#define TYPE_SEAFILE_SERVICE_HANDLER \
  (seafile_service_handler_get_type ())


#define SEAFILE_SERVICE_HANDLER(obj)                                \
  (G_TYPE_CHECK_INSTANCE_CAST ((obj),                                   \
                               TYPE_SEAFILE_SERVICE_HANDLER,        \
                               SeafileServiceHandler))
#define SEAFILE_SERVICE_HANDLER_CLASS(c)                    \
  (G_TYPE_CHECK_CLASS_CAST ((c),                                \
                            TYPE_SEAFILE_SERVICE_HANDLER,   \
                            SeafileServiceHandlerClass))
#define IS_SEAFILE_SERVICE_HANDLER(obj)                             \
  (G_TYPE_CHECK_INSTANCE_TYPE ((obj),                                   \
                               TYPE_SEAFILE_SERVICE_HANDLER))
#define IS_SEAFILE_SERVICE_HANDLER_CLASS(c)                 \
  (G_TYPE_CHECK_CLASS_TYPE ((c),                                \
                            TYPE_SEAFILE_SERVICE_HANDLER))
#define SEAFILE_SERVICE_HANDLER_GET_CLASS(obj)              \
  (G_TYPE_INSTANCE_GET_CLASS ((obj),                            \
                              TYPE_SEAFILE_SERVICE_HANDLER, \
                              SeafileServiceHandlerClass))


struct _SeafileServiceHandler {
  SeafileHandler parent_instance;

  /* private */
  GHashTable *log;
};
typedef struct _SeafileServiceHandler SeafileServiceHandler;

struct _SeafileServiceHandlerClass {
  SeafileHandlerClass parent_class;
};
typedef struct _SeafileServiceHandlerClass SeafileServiceHandlerClass;


GType seafile_service_handler_get_type (void);

G_END_DECLS
