#!/usr/bin/env bash
# =============================================================================
# clang-tidy wrapper — checks compile_commands.json before running clang-tidy
# 优先使用系统已安装且主版本一致的 clang-tidy（与 clang-format v18.1.8、
# .clang-tidy 规则对齐）；缺失或版本不符时下载官方 LLVM 预编译包到 pre-commit
# 缓存目录（首次后复用，与 gitleaks.sh 同约定，国内走 gh-proxy.com 镜像）。
# =============================================================================
set -euo pipefail

BUILD_DIRS=("build")

for dir in "${BUILD_DIRS[@]}"; do
    if [[ -f "${dir}/compile_commands.json" ]]; then
        break
    fi
done

if [[ ! -f "${dir}/compile_commands.json" ]]; then
    cat >&2 <<'EOF'
=======================================================================
  ERROR: compile_commands.json NOT FOUND
-----------------------------------------------------------------------
  clang-tidy requires a compilation database to work.
  Run this command to generate compile_commands.json:

    python3 build.py

  This will generate compile_commands.json under the build/ directory.
=======================================================================
EOF
    exit 1
fi

# ---- 解析 clang-tidy：优先系统同主版本，缺失则下载官方预编译包到缓存 ----
VERSION="18.1.8"
MAJOR="${VERSION%%.*}"
ARCH="$(uname -m)"
CACHE_DIR="${PRE_COMMIT_HOME:-$HOME/.cache/pre-commit}/clang-tidy"
BIN="$CACHE_DIR/bin/clang-tidy"

for cand in "clang-tidy-$MAJOR" clang-tidy; do
    sys_bin="$(command -v "$cand" 2>/dev/null || true)"
    [[ -n "$sys_bin" && "$sys_bin" != "$BIN" && -x "$sys_bin" ]] || continue
    if "$sys_bin" --version 2>/dev/null | grep -q "version $MAJOR\."; then
        exec "$sys_bin" "$@"
    fi
done

if [[ ! -x "$BIN" ]]; then
    case "$ARCH" in
        x86_64|amd64)  ASSET="clang+llvm-${VERSION}-x86_64-linux-gnu-ubuntu-18.04.tar.xz" ;;
        aarch64|arm64) ASSET="clang+llvm-${VERSION}-aarch64-linux-gnu.tar.xz" ;;
        *) echo "unsupported arch: $ARCH" >&2; exit 1 ;;
    esac
    mkdir -p "$CACHE_DIR"
    url="https://gh-proxy.com/https://github.com/llvm/llvm-project/releases/download/llvmorg-${VERSION}/${ASSET}"
    echo "Downloading clang-tidy (LLVM $VERSION, $ARCH) ..." >&2
    archive="$CACHE_DIR/llvm.tar.xz"
    if command -v wget >/dev/null 2>&1; then
        wget --no-check-certificate -c -O "$archive" "$url"
    else
        curl -fL -C - -o "$archive" "$url"
    fi
    # 仅解出 bin/clang-tidy 及其依赖的 lib，保留 $ORIGIN/../lib 的 RPATH
    tar -xJf "$archive" -C "$CACHE_DIR" --strip-components=1 \
        --wildcards '*/bin/clang-tidy' '*/lib/*'
    chmod +x "$BIN"
    rm -f "$archive"
fi

# 官方预编译包基于 Ubuntu 18.04，clang-tidy 依赖 libtinfo.so.5；新系统通常只有 libtinfo.so.6，
# 缺失时给出安装提示，避免直接抛 "cannot open shared object file"。
missing="$(ldd "$BIN" 2>/dev/null | grep 'not found' || true)"
if [[ -n "$missing" ]]; then
    cat >&2 <<EOF
clang-tidy 缺少依赖库：
$missing

官方预编译包基于 Ubuntu 18.04，需 libtinfo5 提供 libtinfo.so.5，请按发行版安装：
  Ubuntu 20.04/22.04、Debian  : sudo apt-get install -y libtinfo5
  openEuler/CentOS/RHEL/Kylin  : sudo dnf install -y ncurses-compat-libs
  Arch                         : yay -S ncurses5-compat-libs
  Ubuntu 24.04（仓库已移除）   : 手动解出旧版 libtinfo.so.5，或将 libtinfo.so.6 软链为 libtinfo.so.5
验证：ldconfig -p | grep libtinfo.so.5
EOF
    exit 1
fi

exec "$BIN" "$@"
