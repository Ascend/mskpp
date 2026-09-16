#!/usr/bin/env bash
# 自动下载官方预编译 gitleaks 二进制到 pre-commit 缓存目录（首次后复用，与 mirrors-clang-format 等同约定）
# 国内走 gh-proxy.com 镜像；升级 gitleaks 时改 VERSION 即可
set -euo pipefail

VERSION="8.30.1"
ARCH="$(uname -m)"
case "$ARCH" in
    x86_64|amd64)  ARCH="x64" ;;
    aarch64|arm64) ARCH="arm64" ;;
    *) echo "unsupported arch: $ARCH" >&2; exit 1 ;;
esac

CACHE_DIR="${PRE_COMMIT_HOME:-$HOME/.cache/pre-commit}/gitleaks"
BIN="$CACHE_DIR/gitleaks"

SYS_BIN="$(command -v gitleaks 2>/dev/null || true)"
if [[ -n "$SYS_BIN" && "$SYS_BIN" != "$BIN" && -x "$SYS_BIN" ]]; then
    exec "$SYS_BIN" "$@"
fi

if [[ ! -x "$BIN" ]]; then
    mkdir -p "$CACHE_DIR"
    url="https://gh-proxy.com/https://github.com/gitleaks/gitleaks/releases/download/v$VERSION/gitleaks_${VERSION}_linux_${ARCH}.tar.gz"
    echo "Downloading gitleaks v$VERSION ($ARCH) ..."
    if command -v wget >/dev/null 2>&1; then
        wget --no-check-certificate -c -O "$CACHE_DIR/gitleaks.tgz" "$url"
    else
        curl -fL -o "$CACHE_DIR/gitleaks.tgz" "$url"
    fi
    tar -xzf "$CACHE_DIR/gitleaks.tgz" -C "$CACHE_DIR" gitleaks
    chmod +x "$BIN"
    rm -f "$CACHE_DIR/gitleaks.tgz"
fi

exec "$BIN" "$@"
