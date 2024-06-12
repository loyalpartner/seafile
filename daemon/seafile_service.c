#include <stdio.h>
#include "seafile-rpc.h"
#include "seafile_service.h"

G_DEFINE_TYPE (SeafileServiceHandler,
              seafile_service_handler,
              TYPE_SEAFILE_HANDLER);

static gboolean
seafile_service_handler_ping (SeafileIf *iface,
                              GError **error)
{
  THRIFT_UNUSED_VAR (iface);
  THRIFT_UNUSED_VAR (error);

  puts ("Ping()");

  return TRUE;
}

static gboolean 
seafile_service_handler_download (SeafileIf *iface,
                                  gchar **_return,
                                  const DownloadRequest *request,
                                  GError **error)
{
  *_return = seafile_download(request->repo_id,
      request->repo_version,
      request->repo_name,
      request->wt_parent,
      request->token,
      request->passwd,
      request->magic,
      request->email,
      request->random_key,
      request->enc_version,
      request->more_info, 
      error
      );

  return TRUE;
}

static gboolean
seafile_service_handler_clone(SeafileIf *iface,
                              gchar **_return,
                              const CloneRequest *request,
                              GError **error)
{

  *_return = seafile_clone(request->repo_id,
      request->repo_version,
      request->repo_name,
      request->worktree,
      request->token,
      request->passwd,
      request->magic,
      request->email,
      request->random_key,
      request->enc_version,
      request->more_info,
      error);

  return TRUE;
}

static void
seafile_service_handler_init (SeafileServiceHandler *self)
{
  self->log = g_hash_table_new_full (g_int_hash,
                                     g_int_equal,
                                     g_free,
                                     g_object_unref);

}


/* TutorialCalculatorHandler's instance finalizer (destructor) */
static void
seafile_service_handler_finalize (GObject *object)
{
  SeafileServiceHandler *self =
    SEAFILE_SERVICE_HANDLER (object);

  /* Free our calculation-log hash table */
  g_hash_table_unref (self->log);
  self->log = NULL;

  /* Chain up to the parent class */
  G_OBJECT_CLASS (seafile_service_handler_parent_class)->
    finalize (object);
}

static void
seafile_service_handler_class_init (SeafileServiceHandlerClass *klass)
{
  GObjectClass *gobject_class = G_OBJECT_CLASS (klass);
  SeafileHandlerClass *seafile_handler_class =
    SEAFILE_HANDLER_CLASS (klass);

  /* Register our destructor */
  gobject_class->finalize = seafile_service_handler_finalize;

  /* Register our implementations of CalculatorHandler's methods */
  seafile_handler_class->ping =
    seafile_service_handler_ping;
  seafile_handler_class->clone =
    seafile_service_handler_clone;
  seafile_handler_class->download =
    seafile_service_handler_download;

}
