#include "seafile-rpc.h"
#include "seafile_service.h"

G_DEFINE_TYPE (SeafileServiceHandler,
              seafile_service_handler,
              TYPE_SEAFILE_HANDLER);

static gboolean
handle_error(GError **error) {
    if (error != NULL && *error != NULL) {
        return FALSE;
    }
    return TRUE;
}

static gboolean
seafile_service_handler_ping (SeafileIf *iface,
                              GError **error)
{
  THRIFT_UNUSED_VAR (iface);
  THRIFT_UNUSED_VAR (error);

  puts ("Ping()");

  return TRUE;
}

gboolean 
seafile_service_set_config (SeafileIf *iface,
                            gint32* _return,
                            const gchar * key,
                            const gchar * value,
                            GError **error)
{
  *_return = seafile_set_config(key, value, error);

  return handle_error(error);
}


gboolean seafile_service_get_config (SeafileIf *iface, 
    gchar ** _return, 
    const gchar * key, 
    GError **error)
{
  *_return = seafile_get_config(key, error);

  return handle_error(error);
}

static gboolean 
seafile_service_handler_download_repo (SeafileIf *iface,
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

  return handle_error(error);
}

static gboolean
seafile_service_handler_clone_repo(SeafileIf *iface,
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

  return handle_error(error);
}

static void
convert_repo (GObject *repo, Repo *r)
{
    g_object_get (repo, 
                  "id", &r->id, "name", &r->name,
                  "desc", &r->desc,
                  "encrypted", &r->encrypted,
                  "worktree", &r->worktree,
                  "auto-sync", &r->auto_sync,
                  "last-sync-time", &r->last_sync_time,
                  "worktree-invalid", &r->worktree_invalid,
                  "relay-id", &r->relay_id,
                  "version", &r->version,
                  NULL);
}


static gboolean
seafile_service_handler_get_repo (SeafileIf *iface,
    Repo **_return,
    const gchar * repo_id,
    GError **error)
{
  GObject *repo = seafile_get_repo(repo_id, error);

  if (repo == NULL) {
    return FALSE;
  }
  convert_repo(repo, *_return);;

  return handle_error(error);
}

static gboolean
seafile_service_handler_destroy_repo (SeafileIf *iface,
    const gchar * repo_id,
    GError **error)
{
  seafile_destroy_repo(repo_id, error);
  return handle_error(error);
}

static gboolean
seafile_service_handler_shutdown (SeafileIf *iface,
    GError **error)
{
  seafile_shutdown(error);
  return handle_error(error);
}

static gboolean
seafile_service_handler_get_repo_list (SeafileIf *iface,
    GPtrArray **_return,
    const gint32 start,
    const gint32 limit,
    GError **error)
{
  GList *repos = seafile_get_repo_list(start, limit, error);
  GList *l;
  for (l = repos; l != NULL; l = l->next) {
    Repo *r = g_object_new(TYPE_REPO, NULL);
    convert_repo(l->data, r);
    g_ptr_array_add(*_return, r);
  }

  return handle_error(error);
}

static void
seafile_service_handler_init (SeafileServiceHandler *self)
{
  self->log = g_hash_table_new_full (g_int_hash,
                                     g_int_equal,
                                     g_free,
                                     g_object_unref);

}

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
  seafile_handler_class->ping = seafile_service_handler_ping;
  seafile_handler_class->set_config =
    seafile_service_set_config;
  seafile_handler_class->get_config =
    seafile_service_get_config;
  seafile_handler_class->clone_repo =
    seafile_service_handler_clone_repo;
  seafile_handler_class->download_repo =
    seafile_service_handler_download_repo;
  seafile_handler_class->get_repo =
    seafile_service_handler_get_repo;
  seafile_handler_class->destroy_repo =
    seafile_service_handler_destroy_repo;
  seafile_handler_class->shutdown =
    seafile_service_handler_shutdown;
  seafile_handler_class->get_repo_list =
    seafile_service_handler_get_repo_list;
}
