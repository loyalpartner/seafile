
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

service Seafile {
  void ping(),

  string download(1: DownloadRequest request),
  string clone(1: CloneRequest request),
}
