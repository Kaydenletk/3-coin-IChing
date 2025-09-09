# I-Ching CLI (3-Coin)

A tiny C program that casts the **I-Ching** with the **3-coin method** and prints a clean, phone-screenshot-friendly result:

- Local **date & time**
- Your **question**
- **Primary hexagram** (King Wen number, Vietnamese name, Inner/Outer trigram)
- **Changing lines** (if any)
- **Resulting hexagram** after changes

> Zero dependencies — just a C11 compiler. Runs on macOS, Linux, Windows (MSYS2/MinGW), Android (Termux), and iOS (iSH).

---

## Demo

⏰ 2025-09-09 15:01:23 PDT
❓ internship 2026 — should I apply to company X?
➤ Quẻ chính: 31 – Trạch Sơn Hàm | Nội:Cấn Ngoại:Đoài
Hào động: 2,5
➤ Quẻ biến : 45 – Trạch Địa Tụy | Nội:Khôn Ngoại:Đoài

yaml
Copy code

---

## Quick Start

### 1) Clone

```bash git clone https://github.com/<your-username>/I-ching-mini.git
cd I-ching-mini
2) Build
macOS


bash # clang is available with Xcode Command Line Tools
cc -O2 -std=c11 iching.c -o iching
Ubuntu/Debian

bash sudo apt update && sudo apt install -y build-essential
gcc -O2 -std=c11 iching.c -o iching
Windows (MSYS2 / MinGW)

bash
Copy code
# In MSYS2 Mingw64 shell
pacman -S --needed mingw-w64-x86_64-gcc
gcc -O2 -std=c11 iching.c -o iching.exe
Android (Termux)

bash
Copy code
pkg update && pkg install clang
clang -O2 iching.c -o iching
iOS (iSH)

bash
Copy code
apk update && apk add build-base
gcc -O2 -std=c11 iching.c -o iching
Run
bash
Copy code
./iching
# Program prompts:
# CÂU HỎI: <type your question and press Enter>
Timezone (important)
The program uses your shell’s timezone. If it’s wrong (e.g., a container set to UTC), set TZ when running:

bash
Copy code
TZ=America/New_York   ./iching   # Eastern
TZ=America/Chicago    ./iching   # Central
TZ=America/Denver     ./iching   # Mountain
TZ=America/Los_Angeles ./iching  # Pacific
TZ=America/Phoenix    ./iching   # Arizona (no DST)
TZ=Pacific/Honolulu   ./iching   # Hawaii
iSH (set once):

bash
Copy code
apk add tzdata
ln -sf /usr/share/zoneinfo/America/Los_Angeles /etc/localtime
echo "America/Los_Angeles" > /etc/timezone
Compile-time default (optional):

bash
Copy code
gcc -O2 -std=c11 iching.c -DUS_TZ=\"America/Los_Angeles\" -o iching
(The code checks US_TZ at startup and falls back to your environment if unset.)

What It Prints
⏰ Local timestamp (timezone shown if provided by libc)

❓ Your exact question

➤ Quẻ chính Primary hexagram — King Wen number + Vietnamese name + inner/outer trigrams

Hào động List of moving lines (empty → no changes)

➤ Quẻ biến Resulting hexagram after applying changes

Under the hood:

3 coins × 6 throws (bottom → top), values 6/7/8/9

Full 64-hexagram King Wen mapping

Vietnamese names embedded in iching.c

Tips
Don’t commit compiled binaries. Use .gitignore:

gitignore
Copy code
*.o
*.out
*.exe
*.a
*.so
*.dylib
*.dSYM/
iching
shot
wenwang
For scripting (no interactive prompt), you can pipe the question:

bash
Copy code
echo "Should I apply to X?" | ./iching
FAQ
Q: Results change each run — is that expected?
Yes. The coin tosses are random; the program seeds with current time.

Q: Can I get a full Wen-Wang six-lines output (Six Gods, Six Relations, 世/应, etc.)?
This repo focuses on clean screenshots. If you want the full version, open an issue — there’s a wenwang_full.c variant.
