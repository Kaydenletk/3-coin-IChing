# I-ching-mini

A tiny C program that casts the I-Ching using the 3-coin method.
It prints exactly what most people need for a quick reading and a clean screenshot:

Local date & time

Your question

Primary hexagram (number, Vietnamese name, Inner/Outer trigram)

Changing lines (if any)

Resulting hexagram (after changes)

Built for terminals on macOS, Linux, Windows, Android (Termux), and iOS (iSH).
No dependencies—just a C11 compiler.

Demo
⏰ 2025-09-09 15:01:23 PDT
❓ internship 2026 — should I apply to company X?
➤ Quẻ chính: 31 – Trạch Sơn Hàm  | Nội:Cấn  Ngoại:Đoài
   Hào động: 2,5
➤ Quẻ biến : 45 – Trạch Địa Tụy  | Nội:Khôn Ngoại:Đoài

Quick start
1) Clone
git clone https://github.com/<your-username>/I-ching-mini.git
cd I-ching-mini

2) Build
macOS
# clang comes with Xcode Command Line Tools
cc -O2 -std=c11 iching.c -o iching

Ubuntu/Debian
sudo apt update && sudo apt install -y build-essential
gcc -O2 -std=c11 iching.c -o iching

Windows (MSYS2 / MinGW)
# In MSYS2 Mingw64 shell
pacman -S --needed mingw-w64-x86_64-gcc
gcc -O2 -std=c11 iching.c -o iching.exe

Android (Termux)
pkg update && pkg install clang
clang -O2 iching.c -o iching

iOS (iSH)
apk update && apk add build-base
gcc -O2 -std=c11 iching.c -o iching

Run
./iching
# Program prompts:
# CÂU HỎI: <type your question and press Enter>

Timezone (important)

The program uses your environment’s timezone. If your shell is UTC or the wrong zone, set TZ when running:

TZ=America/New_York ./iching      # Eastern
TZ=America/Chicago ./iching       # Central
TZ=America/Denver ./iching        # Mountain
TZ=America/Los_Angeles ./iching   # Pacific
TZ=America/Phoenix ./iching       # Arizona (no DST)
TZ=Pacific/Honolulu ./iching      # Hawaii


iSH only (set once):

apk add tzdata
ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime
echo "America/Los_Angeles" > /etc/timezone

What it prints

⏰ Local timestamp (with timezone if your libc provides it)

❓ Your question (exactly what you typed)

➤ Quẻ chính Primary hexagram (King Wen number + Vietnamese name), inner/outer trigrams

Hào động List of moving lines (empty → no changes)

➤ Quẻ biến Resulting hexagram after applying moving lines

Under the hood:

3 coins × 6 throws (bottom → top), values 6/7/8/9

Full 64-hexagram King Wen mapping

Vietnamese names included in iching.c

Tips

Want US timezone baked into the binary?

gcc -O2 -std=c11 iching.c -DUS_TZ=\"America/Los_Angeles\" -o iching


(The code checks US_TZ at startup and falls back to your environment.)

No need to push compiled binaries to Git—just the source. See .gitignore.

FAQ

Q: I run it twice and get different results. Is that normal?
A: Yes—coin tosses are random. The program seeds with current time.

Q: Can I get a “full Wen-Wang six-lines” table (Six Gods, Six Relations, 世/应, etc.)?
A: This repo focuses on a clean screenshot output. If you need the full version, open an issue—we also have a more detailed wenwang_full.c.

Contributing

Issues and PRs welcome. Keep it C11-only, zero external deps, and portable.

License

MIT © You, the repo owner.
