#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAX_FILES       4096   // max files tracked by scan/organize
#define MAX_DIRS        4096   // max directories tracked by the walk stack (search/dupes/report)
#define MAX_PATH_LEN    512
#define MAX_NAME_LEN    256
#define MAX_EXT_LEN     32
#define NUM_CATEGORIES  6
#define MAX_EXTS_PER_CATEGORY 8

// ---------------------------------------------------------------------------
// Data
// ---------------------------------------------------------------------------

static const char *CATEGORY_NAMES[NUM_CATEGORIES + 1] = {
    "Images", "Documents", "Videos", "Audio", "Archives", "Programs", "Others"
};

// BUG FIX (original bug): extensions were stored in a NULL-terminated array,
// but the "Documents" row had exactly 8 entries and no NULL terminator.
// get_category() scanned until it hit NULL, so it walked off the end of that
// row into neighboring memory (the "Videos" row), which is why .avi/.mov
// files were being misclassified as "Documents" in the original program.
//
// Fix: store an explicit count per category instead of relying on a NULL
// sentinel. This removes the bug class entirely (no risk of a missing
// terminator ever causing an out-of-bounds read again).
static const char *CATEGORY_EXTS[NUM_CATEGORIES][MAX_EXTS_PER_CATEGORY] = {
    { ".jpg", ".jpeg", ".png", ".gif", ".bmp", ".webp" },
    { ".pdf", ".doc", ".docx", ".txt", ".ppt", ".pptx", ".xls", ".xlsx" },
    { ".mp4", ".avi", ".mkv", ".mov", ".wmv" },
    { ".mp3", ".wav", ".aac", ".flac" },
    { ".zip", ".rar", ".7z", ".tar", ".gz" },
    { ".exe", ".msi", ".apk", ".py", ".c", ".cpp", ".java" }
};

static const int CATEGORY_EXT_COUNT[NUM_CATEGORIES] = { 6, 8, 5, 4, 5, 7 };

// ---------------------------------------------------------------------------
// Organizer state
// ---------------------------------------------------------------------------

typedef struct {
    char folder_path[MAX_PATH_LEN];
    char files[MAX_FILES][MAX_NAME_LEN];
    int  file_count;
    int  stats[NUM_CATEGORIES + 1];  // last slot = "Others"
} Organizer;

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

// Safe, always-null-terminated string copy (strncpy doesn't guarantee this
// if src is >= n chars long, which was a latent bug in several spots).
static void safe_copy(char *dst, size_t dst_size, const char *src) {
    if (dst_size == 0) return;
    strncpy(dst, src, dst_size - 1);
    dst[dst_size - 1] = '\0';
}

static void str_lower(char *s) {
    for (; *s; s++) {
        if (*s >= 'A' && *s <= 'Z') *s += 32;
    }
}

static const char *get_extension(const char *filename) {
    const char *dot = strrchr(filename, '.');
    return (dot && dot != filename) ? dot : "";
}

static int get_category(const char *ext) {
    char lower[MAX_EXT_LEN];
    safe_copy(lower, sizeof(lower), ext);
    str_lower(lower);

    for (int c = 0; c < NUM_CATEGORIES; c++) {
        for (int e = 0; e < CATEGORY_EXT_COUNT[c]; e++) {
            if (strcmp(lower, CATEGORY_EXTS[c][e]) == 0) return c;
        }
    }
    return NUM_CATEGORIES;  // "Others"
}

// Build "folder\subfolder" safely
static void join_path(char *out, int out_size, const char *base, const char *sub) {
    snprintf(out, out_size, "%s\\%s", base, sub);
}

// ---------------------------------------------------------------------------
// Module 1 - Validate directory
// ---------------------------------------------------------------------------

static int validate_directory(Organizer *org) {
    DWORD attr = GetFileAttributesA(org->folder_path);
    if (attr == INVALID_FILE_ATTRIBUTES) {
        printf("Folder does not exist.\n");
        return 0;
    }
    if (!(attr & FILE_ATTRIBUTE_DIRECTORY)) {
        printf("Invalid directory.\n");
        return 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
// Module 2 - Scan files
// ---------------------------------------------------------------------------

static void scan_files(Organizer *org) {
    org->file_count = 0;

    char pattern[MAX_PATH_LEN];
    join_path(pattern, MAX_PATH_LEN, org->folder_path, "*");

    WIN32_FIND_DATAA fd;
    HANDLE h = FindFirstFileA(pattern, &fd);
    if (h == INVALID_HANDLE_VALUE) {
        printf("Error opening directory.\n");
        return;
    }

    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        if (org->file_count >= MAX_FILES) {
            printf("Warning: too many files, only first %d scanned.\n", MAX_FILES);
            break;
        }
        safe_copy(org->files[org->file_count], MAX_NAME_LEN, fd.cFileName);
        org->file_count++;
    } while (FindNextFileA(h, &fd));

    FindClose(h);

    printf("\nFound %d files\n\n", org->file_count);
    for (int i = 0; i < org->file_count; i++) {
        printf("%s -> %s\n", org->files[i], get_extension(org->files[i]));
    }
}

// ---------------------------------------------------------------------------
// Module 3 - Organize files
// ---------------------------------------------------------------------------

static void organize_files(Organizer *org) {
    memset(org->stats, 0, sizeof(org->stats));

    // Create all category folders
    for (int c = 0; c <= NUM_CATEGORIES; c++) {
        char dir[MAX_PATH_LEN];
        join_path(dir, MAX_PATH_LEN, org->folder_path, CATEGORY_NAMES[c]);
        CreateDirectoryA(dir, NULL);  // ok if already exists
    }

    for (int i = 0; i < org->file_count; i++) {
        char src[MAX_PATH_LEN];
        join_path(src, MAX_PATH_LEN, org->folder_path, org->files[i]);

        if (GetFileAttributesA(src) == INVALID_FILE_ATTRIBUTES) continue;

        int cat = get_category(get_extension(org->files[i]));

        char dst[MAX_PATH_LEN];
        snprintf(dst, MAX_PATH_LEN, "%s\\%s\\%s",
                 org->folder_path, CATEGORY_NAMES[cat], org->files[i]);

        if (!MoveFileA(src, dst)) {
            DWORD err = GetLastError();
            if (err == ERROR_ALREADY_EXISTS || err == ERROR_FILE_EXISTS) {
                printf("%s already exists in %s\n", org->files[i], CATEGORY_NAMES[cat]);
            } else {
                printf("Failed to move %s (error %lu)\n", org->files[i], err);
            }
        } else {
            org->stats[cat]++;
        }
    }

    printf("\nFiles organized successfully.\n");
}

// ---------------------------------------------------------------------------
// Module 4 - Show statistics
// ---------------------------------------------------------------------------

static void show_statistics(Organizer *org) {
    int total = 0;

    printf("\n==============================\n");
    printf("      FILE STATISTICS\n");
    printf("==============================\n");

    for (int c = 0; c <= NUM_CATEGORIES; c++) {
        printf("%-15s%d\n", CATEGORY_NAMES[c], org->stats[c]);
        total += org->stats[c];
    }

    printf("------------------------------\n");
    printf("%-15s%d\n", "Total Files", total);
    printf("==============================\n");
}

// ---------------------------------------------------------------------------
// Module 5 - Search files (recursive walk via explicit stack)
// ---------------------------------------------------------------------------

typedef struct {
    char dirs[MAX_DIRS][MAX_PATH_LEN];
    int  top;
} DirStack;

// BUG FIX: original stack_push() had no bounds message and silently dropped
// pushes once full with no warning at all; also it shared MAX_FILES as its
// capacity even though it stores directories, not files. Now it has its own
// MAX_DIRS capacity and warns once if exceeded.
static void stack_push(DirStack *s, const char *path) {
    if (s->top < MAX_DIRS) {
        safe_copy(s->dirs[s->top], MAX_PATH_LEN, path);
        s->top++;
    } else {
        printf("Warning: directory stack full, some folders skipped.\n");
    }
}

static void walk_and_search(const char *root, int by_name, const char *keyword) {
    DirStack *stack = (DirStack *)malloc(sizeof(DirStack));
    if (!stack) { printf("Out of memory.\n"); return; }
    stack->top = 0;
    stack_push(stack, root);

    int found = 0;

    char lower_kw[MAX_NAME_LEN];
    safe_copy(lower_kw, MAX_NAME_LEN, keyword);
    str_lower(lower_kw);

    while (stack->top > 0) {
        char current[MAX_PATH_LEN];
        safe_copy(current, MAX_PATH_LEN, stack->dirs[--stack->top]);

        char pattern[MAX_PATH_LEN];
        join_path(pattern, MAX_PATH_LEN, current, "*");

        WIN32_FIND_DATAA fd;
        HANDLE h = FindFirstFileA(pattern, &fd);
        if (h == INVALID_HANDLE_VALUE) continue;

        do {
            if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;

            char full[MAX_PATH_LEN];
            join_path(full, MAX_PATH_LEN, current, fd.cFileName);

            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                stack_push(stack, full);
            } else {
                char lower_name[MAX_NAME_LEN];
                safe_copy(lower_name, MAX_NAME_LEN, fd.cFileName);
                str_lower(lower_name);

                int match;
                if (by_name) {
                    match = (strstr(lower_name, lower_kw) != NULL);
                } else {
                    // match extension exactly
                    const char *ext = get_extension(lower_name);
                    match = (strcmp(ext, lower_kw) == 0);
                }

                if (match) {
                    printf("%s\n", full);
                    found = 1;
                }
            }
        } while (FindNextFileA(h, &fd));

        FindClose(h);
    }

    free(stack);

    if (!found) printf("No matching files found.\n");
}

static void search_files(Organizer *org) {
    printf("\n1. Search by Name\n");
    printf("2. Search by Extension\n");
    printf("Enter choice: ");

    char choice[8];
    if (!fgets(choice, sizeof(choice), stdin)) return;
    choice[strcspn(choice, "\r\n")] = '\0';

    printf("\n");

    if (strcmp(choice, "1") == 0) {
        printf("Enter file name: ");
        char keyword[MAX_NAME_LEN];
        if (!fgets(keyword, sizeof(keyword), stdin)) return;
        keyword[strcspn(keyword, "\r\n")] = '\0';
        printf("\n");
        walk_and_search(org->folder_path, 1, keyword);

    } else if (strcmp(choice, "2") == 0) {
        printf("Enter extension (Example: .pdf): ");
        char ext[MAX_EXT_LEN];
        if (!fgets(ext, sizeof(ext), stdin)) return;
        ext[strcspn(ext, "\r\n")] = '\0';
        printf("\n");
        walk_and_search(org->folder_path, 0, ext);

    } else {
        printf("Invalid choice.\n");
    }
}

// ---------------------------------------------------------------------------
// Module 6 - Find duplicates (shared hash-table helper used by report too)
// ---------------------------------------------------------------------------

#define HASH_SIZE 8191

typedef struct HashNode {
    char name[MAX_NAME_LEN];
    struct HashNode *next;
} HashNode;

static unsigned int hash_str(const char *s) {
    unsigned int h = 5381;
    while (*s) h = h * 33 + (unsigned char)*s++;
    return h % HASH_SIZE;
}

static void free_hash_table(HashNode *table[HASH_SIZE]) {
    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode *n = table[i];
        while (n) {
            HashNode *tmp = n;
            n = n->next;
            free(tmp);
        }
    }
}

// Walks the whole tree, calling back for every file found (not just dirs).
// skip_name (optional) lets the caller exclude a specific file, e.g. the
// report file itself, from being treated as a duplicate.
static int collect_duplicates(const char *root, const char *skip_name,
                               void (*on_dup)(const char *name, void *ctx), void *ctx) {
    HashNode *table[HASH_SIZE];
    memset(table, 0, sizeof(table));
    int dup_found = 0;

    DirStack *stack = (DirStack *)malloc(sizeof(DirStack));
    if (!stack) { printf("Out of memory.\n"); return 0; }
    stack->top = 0;
    stack_push(stack, root);

    while (stack->top > 0) {
        char current[MAX_PATH_LEN];
        safe_copy(current, MAX_PATH_LEN, stack->dirs[--stack->top]);

        char pattern[MAX_PATH_LEN];
        join_path(pattern, MAX_PATH_LEN, current, "*");

        WIN32_FIND_DATAA fd;
        HANDLE h = FindFirstFileA(pattern, &fd);
        if (h == INVALID_HANDLE_VALUE) continue;

        do {
            if (strcmp(fd.cFileName, ".") == 0 || strcmp(fd.cFileName, "..") == 0) continue;
            if (skip_name && strcmp(fd.cFileName, skip_name) == 0) continue;

            char full[MAX_PATH_LEN];
            join_path(full, MAX_PATH_LEN, current, fd.cFileName);

            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                stack_push(stack, full);
            } else {
                unsigned int idx = hash_str(fd.cFileName);
                HashNode *node = table[idx];
                int found_in_table = 0;
                while (node) {
                    if (strcmp(node->name, fd.cFileName) == 0) { found_in_table = 1; break; }
                    node = node->next;
                }
                if (found_in_table) {
                    dup_found = 1;
                    on_dup(fd.cFileName, ctx);
                } else {
                    HashNode *new_node = (HashNode *)malloc(sizeof(HashNode));
                    safe_copy(new_node->name, MAX_NAME_LEN, fd.cFileName);
                    new_node->next = table[idx];
                    table[idx] = new_node;
                }
            }
        } while (FindNextFileA(h, &fd));

        FindClose(h);
    }

    free(stack);
    free_hash_table(table);
    return dup_found;
}

static void print_dup_console(const char *name, void *ctx) {
    (void)ctx;
    printf("%s\n", name);
}

static void find_duplicates(Organizer *org) {
    printf("\n");
    int dup_found = collect_duplicates(org->folder_path, NULL, print_dup_console, NULL);
    if (dup_found) {
        printf("(Duplicate files found above)\n");
    } else {
        printf("No Duplicate Files Found.\n");
    }
}

static void print_dup_to_file(const char *name, void *ctx) {
    FILE *f = (FILE *)ctx;
    fprintf(f, "%s\n", name);
}

// ---------------------------------------------------------------------------
// Module 7 - Generate report
// ---------------------------------------------------------------------------

static void generate_report(Organizer *org) {
    char report_path[MAX_PATH_LEN];
    join_path(report_path, MAX_PATH_LEN, org->folder_path, "file_report.txt");

    FILE *f = fopen(report_path, "w");
    if (!f) {
        printf("Error generating report.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char date_buf[32];
    strftime(date_buf, sizeof(date_buf), "%d-%m-%Y %H:%M:%S", t);

    fprintf(f, "SMART FILE ORGANIZER REPORT\n");
    fprintf(f, "========================================\n\n");
    fprintf(f, "Date   : %s\n", date_buf);
    fprintf(f, "Folder : %s\n\n", org->folder_path);

    int total = 0;
    for (int c = 0; c <= NUM_CATEGORIES; c++) total += org->stats[c];

    fprintf(f, "Total Files : %d\n\n", total);

    fprintf(f, "Category-wise Count\n");
    fprintf(f, "-------------------------\n");
    for (int c = 0; c <= NUM_CATEGORIES; c++) {
        fprintf(f, "%-15s%d\n", CATEGORY_NAMES[c], org->stats[c]);
    }
    fprintf(f, "\n");

    fprintf(f, "Duplicate Files\n");
    fprintf(f, "-------------------------\n");

    int dup_found = collect_duplicates(org->folder_path, "file_report.txt", print_dup_to_file, f);
    if (!dup_found) fprintf(f, "No Duplicate Files Found\n");

    fprintf(f, "\nFolder Structure\n");
    fprintf(f, "-------------------------\n");

    char list_pattern[MAX_PATH_LEN];
    join_path(list_pattern, MAX_PATH_LEN, org->folder_path, "*");

    WIN32_FIND_DATAA fd2;
    HANDLE h2 = FindFirstFileA(list_pattern, &fd2);
    if (h2 != INVALID_HANDLE_VALUE) {
        do {
            if (fd2.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
                if (strcmp(fd2.cFileName, ".") != 0 && strcmp(fd2.cFileName, "..") != 0) {
                    fprintf(f, "%s\n", fd2.cFileName);
                }
            }
        } while (FindNextFileA(h2, &fd2));
        FindClose(h2);
    }

    fclose(f);
    printf("\nReport generated successfully.\n");
    printf("Saved as: %s\n", report_path);
}

// ---------------------------------------------------------------------------
// Main
// ---------------------------------------------------------------------------

int main(void) {
    Organizer org;
    memset(&org, 0, sizeof(org));

    printf("=============================================\n");
    printf("        SMART FILE ORGANIZER\n");
    printf("=============================================\n");

    printf("Enter Folder Path: ");
    if (!fgets(org.folder_path, MAX_PATH_LEN, stdin)) return 1;
    org.folder_path[strcspn(org.folder_path, "\r\n")] = '\0';

    if (!validate_directory(&org)) return 1;

    char choice[8];

    while (1) {
        printf("\n========== MENU ==========\n");
        printf("1. Scan Files\n");
        printf("2. Organize Files\n");
        printf("3. Show Statistics\n");
        printf("4. Search Files\n");
        printf("5. Find Duplicates\n");
        printf("6. Generate Report\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        if (!fgets(choice, sizeof(choice), stdin)) break;
        choice[strcspn(choice, "\r\n")] = '\0';

        if (strcmp(choice, "1") == 0) {
            scan_files(&org);

        } else if (strcmp(choice, "2") == 0) {
            if (org.file_count == 0) scan_files(&org);
            organize_files(&org);

        } else if (strcmp(choice, "3") == 0) {
            show_statistics(&org);

        } else if (strcmp(choice, "4") == 0) {
            search_files(&org);

        } else if (strcmp(choice, "5") == 0) {
            find_duplicates(&org);

        } else if (strcmp(choice, "6") == 0) {
            generate_report(&org);

        } else if (strcmp(choice, "7") == 0) {
            printf("Thank you for using Smart File Organizer.\n");
            break;

        } else {
            printf("Invalid choice.\n");
        }
    }

    return 0;
}