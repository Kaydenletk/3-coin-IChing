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


----
## Quick Start

### 1) Clone
macOS
```bash git clone https://github.com/<your-username>/I-ching-mini.git
cd I-ching-mini
2) Build


apk update && apk add build-base
gcc -O2 -std=c11 iching.c -o iching

Run
# Program prompts:
# CÂU HỎI: <type your question and press Enter>
Timezone (important)
The program uses your shell’s timezone. If it’s wrong (e.g., a container set to UTC), set TZ when running:

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
