
struct DownloadRequest {
  1: string repo_id,
  2: i32 repo_version,
  3: string repo_name,
  4: string wt_parent,
  5: string token,
  6: string passwd,
  7: string magic,
  8: string email,
  9: string random_key,
  10: i32 enc_version,
  11: string more_info,
}

struct CloneRequest {
  1: string repo_id,
  2: i32 repo_version,
  3: string repo_name,
  4: string worktree,
  5: string token,
  6: string passwd,
  7: string magic,
  8: string email,
  9: string random_key,
  10: i32 enc_version,
  11: string more_info,
}

struct Repo {
    1: string id,
    2: string name,
    3: string desc,
    4: bool encrypted,
    5: string worktree,
    6: bool auto_sync,
    7: i64 last_sync_time,
    8: bool worktree_invalid,
    9: string relay_id,
    10: i32 version,
}

service Seafile {
  void ping(),

  i32 set_config(1: string key, 2: string value),
  string get_config(1: string key),
  string download_repo(1: DownloadRequest request),
  string clone_repo(1: CloneRequest request),
  Repo get_repo(1: string repo_id),
  void destroy_repo(1: string repo_id),
  void shutdown(),
  list<Repo> get_repo_list(1: i32 start, 2: i32 limit),
}
