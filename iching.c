// file: iching_mini.c
// Mục tiêu: output cực gọn cho screenshot trên điện thoại.
// ✓ Gieo 3 đồng xu × 6 hào (dưới→trên)  ✓ 64 quẻ King Wen  ✓ Quẻ biến
// ✓ In: Thời điểm, Câu hỏi, Quẻ chính, Hào động, Quẻ biến. (mỗi mục 1 dòng)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

static int toss(void) { return rand() % 2; } // 1=H, 0=T
static int heads_to_val(int h) { return h == 3 ? 9 : h == 2 ? 7
                                                 : h == 1   ? 8
                                                            : 6; } // 9/7 dương; 8/6 âm
static int is_yang(int v) { return (v == 7 || v == 9); }
static int changed_val(int v) { return v == 9 ? 8 : v == 6 ? 7
                                                           : v; }

// Trigram mapping bottom->top bits → index: 0..7 = Càn, Đoài, Ly, Chấn, Tốn, Khảm, Cấn, Khôn
static int bits_to_trigram(int b1, int b2, int b3)
{
    int code = (b1 ? 1 : 0) | (b2 ? 2 : 0) | (b3 ? 4 : 0);
    static const int map[8] = {7, 3, 5, 1, 6, 2, 4, 0}; // 000→Khôn..111→Càn
    return map[code];
}
static const char *TRI_S[] = {"Càn", "Đoài", "Ly", "Chấn", "Tốn", "Khảm", "Cấn", "Khôn"};

// King Wen: lower row, upper column (order ☰ ☱ ☲ ☳ ☴ ☵ ☶ ☷)
static const int KW_TABLE[8][8] = {
    /* ☰   ☱   ☲   ☳   ☴   ☵   ☶   ☷  */
    {1, 43, 14, 34, 9, 5, 26, 11},
    {10, 58, 38, 54, 61, 60, 41, 19},
    {13, 49, 30, 55, 37, 63, 22, 36},
    {25, 17, 21, 51, 42, 3, 27, 24},
    {44, 28, 50, 32, 57, 48, 18, 46},
    {6, 47, 64, 40, 59, 29, 4, 7},
    {33, 31, 56, 62, 53, 39, 52, 15},
    {12, 45, 35, 16, 20, 8, 23, 2}};
static const char *KW_NAME_VI[65] = {
    "", "Càn – Thuần Càn", "Khôn – Thuần Khôn", "Thủy Lôi Truân", "Sơn Thủy Mông", "Thủy Thiên Nhu", "Thiên Thủy Tụng", "Địa Thủy Sư", "Thủy Địa Tỷ",
    "Phong Thiên Tiểu Súc", "Thiên Trạch Lý", "Địa Thiên Thái", "Thiên Địa Bĩ", "Hỏa Thiên Đồng Nhân", "Thiên Hỏa Đại Hữu", "Địa Sơn Khiêm", "Lôi Địa Dự",
    "Trạch Lôi Tùy", "Sơn Phong Cổ", "Địa Trạch Lâm", "Phong Địa Quán", "Hỏa Lôi Thị Hạp", "Sơn Hỏa Bí", "Sơn Địa Bác", "Địa Lôi Phục", "Thiên Lôi Vô Vọng",
    "Sơn Thiên Đại Súc", "Sơn Lôi Di", "Trạch Phong Đại Quá", "Thuần Khảm", "Thuần Ly", "Trạch Sơn Hàm", "Phong Lôi Hằng", "Thiên Sơn Độn", "Lôi Thiên Đại Tráng",
    "Hỏa Địa Tấn", "Địa Hỏa Minh Di", "Phong Hỏa Gia Nhân", "Hỏa Trạch Khuê", "Thủy Sơn Kiển", "Lôi Thủy Giải", "Sơn Trạch Tổn", "Phong Lôi Ích", "Trạch Thiên Quải",
    "Thiên Phong Cấu", "Trạch Địa Tụy", "Địa Phong Thăng", "Trạch Thủy Khốn", "Thủy Phong Tỉnh", "Trạch Hỏa Cách", "Hỏa Phong Đỉnh", "Thuần Chấn", "Thuần Cấn",
    "Phong Sơn Tiệm", "Lôi Trạch Quy Muội", "Lôi Hỏa Phong", "Hỏa Sơn Lữ", "Thuần Tốn", "Thuần Đoài", "Phong Thủy Hoán", "Thủy Trạch Tiết", "Phong Trạch Trung Phu",
    "Lôi Sơn Tiểu Quá", "Thủy Hỏa Ký Tế", "Hỏa Thủy Vị Tế"};

int main(void)
{
    srand((unsigned)time(NULL));

    // 1) Nhập câu hỏi
    char question[512];
    printf("CÂU HỎI: ");
    if (!fgets(question, sizeof(question), stdin))
        question[0] = '\0';
    question[strcspn(question, "\r\n")] = 0;

    // 2) Lấy thời gian hiện tại (local)
    time_t now = time(NULL);
    struct tm *tmp = localtime(&now);
    struct tm lt = tmp ? *tmp : (struct tm){0};
    char ts[32];
    strftime(ts, sizeof(ts), "%Y-%m-%d %H:%M", &lt);

    // 3) Gieo 6 hào (dưới→trên)
    int base[6], chg[6];
    int moving_count = 0;
    int moving_list[6]; // lưu hào động
    for (int i = 0; i < 6; i++)
    {
        int heads = toss() + toss() + toss(); // 0..3
        int val = heads_to_val(heads);
        base[i] = val;
        chg[i] = changed_val(val);
        if (val == 6 || val == 9)
            moving_list[moving_count++] = i + 1;
    }

    // 4) Tính quẻ chính & quẻ biến
    int lower = bits_to_trigram(is_yang(base[0]), is_yang(base[1]), is_yang(base[2]));
    int upper = bits_to_trigram(is_yang(base[3]), is_yang(base[4]), is_yang(base[5]));
    int kw = KW_TABLE[lower][upper];

    int lower2 = bits_to_trigram(is_yang(chg[0]), is_yang(chg[1]), is_yang(chg[2]));
    int upper2 = bits_to_trigram(is_yang(chg[3]), is_yang(chg[4]), is_yang(chg[5]));
    int kw2 = KW_TABLE[lower2][upper2];

    // 5) In siêu gọn (mỗi mục 1 dòng)
    printf("\n⏰ %s\n", ts);
    printf("❓ %s\n", question[0] ? question : "(chưa nhập)");
    printf("➤ Quẻ chính: %02d – %s  | Nội:%s  Ngoại:%s\n",
           kw, KW_NAME_VI[kw], TRI_S[lower], TRI_S[upper]);

    printf("   Hào động: ");
    if (moving_count == 0)
        printf("(không có)\n");
    else
    {
        for (int i = 0; i < moving_count; i++)
        {
            if (i)
                putchar(',');
            printf("%d", moving_list[i]);
        }
        printf("\n");
    }

    printf("➤ Quẻ biến : %02d – %s  | Nội:%s  Ngoại:%s\n",
           kw2, KW_NAME_VI[kw2], TRI_S[lower2], TRI_S[upper2]);
    return 0;
}
