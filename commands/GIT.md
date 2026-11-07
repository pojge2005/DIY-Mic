# Git Command Guide

Run Git commands in Ubuntu Terminal from the repository directory.

## 1. Inspect repository state

```bash
git status --short --branch
git branch --show-current
git log -5 --oneline --decorate
git diff --check
git diff
```

| Command | Purpose | Use case |
|---|---|---|
| `git status --short --branch` | Show branch and working-tree changes | Before and after work |
| `git branch --show-current` | Print current branch | Confirm target branch |
| `git log -5 --oneline --decorate` | Show recent commits | Review project history |
| `git diff --check` | Detect whitespace errors | Pre-commit check |
| `git diff` | Review unstaged changes | Inspect exact edits |

## 2. Switch to the documentation branch

```bash
git fetch origin
git switch dev/esp32-s3-ble-bringup
git pull --ff-only origin dev/esp32-s3-ble-bringup
```

**Purpose:** update local remote references and fast-forward the local branch.  
**Use case:** begin work on the ESP32-S3 documentation/bring-up branch.

## 3. Stage and commit

```bash
git add README.md commands docs ESP32-S3 tests
git diff --cached --check
git diff --cached
git commit -m "docs: organize project commands and test logs"
```

Review the staged diff before committing. Adjust the `git add` paths if only a subset of files is intended.

## 4. Push the branch

```bash
git push origin dev/esp32-s3-ble-bringup
```

**Purpose:** publish local commits to the remote branch.  
**Use case:** share documentation changes and preserve the work on GitHub.

## 5. Safety

- Do not use `git reset --hard`, force-push, or delete branches as routine cleanup.
- Do not commit credentials, tokens, private keys, or unredacted logs.
- Do not stage unrelated firmware changes with documentation-only changes.
- If push is rejected, inspect `git status` and remote history before deciding how to reconcile.
