#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <direct.h>   // Windows
    #define CREATE_DIR(name) _mkdir(name)
    #define SEP "\\"
#else
    #include <sys/stat.h>  // Linux / Mac
    #include <sys/types.h>
    #include <unistd.h>
    #define CREATE_DIR(name) mkdir(name, 0777)
    #define SEP "/"
#endif

char *files[] = {"abc.txt", "xyz.txt", "conference.txt"};
int file_count = 3;

// Function to update University folder files
void updateUniversity(char *depts[], int deptCount) {
    char uniPath[200], deptPath[200], buffer[500];

    CREATE_DIR("University");  // Ensure University folder exists

    for (int i = 0; i < file_count; i++) {
        sprintf(uniPath, "University%s%s", SEP, files[i]);
        FILE *uni = fopen(uniPath, "w");  // Clear and rewrite file

        if (uni == NULL) {
            printf("❌ Error creating %s\n", uniPath);
            continue;
        }

        // Merge all department data into University file
        for (int d = 0; d < deptCount; d++) {
            sprintf(deptPath, "%s%s%s", depts[d], SEP, files[i]);
            FILE *deptFile = fopen(deptPath, "r");

            if (deptFile != NULL) {
                fprintf(uni, "\n==== %s ====\n", depts[d]);  // Section header
                while (fgets(buffer, sizeof(buffer), deptFile)) {
                    fputs(buffer, uni);  // Copy line to University file
                }
                fclose(deptFile);
            } else {
                printf("⚠ Missing file: %s\n", deptPath);
            }
        }

        fclose(uni);
        printf("✅ Updated %s\n", uniPath);
    }
}

int main() {
    // Departments list (you can add/remove dynamically)
    char *depts[] = {"MCA", "BCA", "MBA"};
    int deptCount = 3;

    updateUniversity(depts, deptCount);

    printf("\n🎉 All University files updated successfully!\n");
    return 0;
}
