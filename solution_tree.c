#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 Student 선언
typedef struct Student {
    char name[20];
    int midterm;
    int final;
    struct Student* left;
    struct Student* right;
} Student;

// Student* 는 구조체 Student의 포인터
Student* createStudent(const char* name, int midterm, int final) {
    Student* newStudent = (Student*)malloc(sizeof(Student));
    strcpy(newStudent->name, name);
    newStudent->midterm = midterm;
    newStudent->final = final;
    newStudent->left = newStudent->right = NULL;
    return newStudent;
}

Student* insertStudent(Student* root, Student* newStudent) {
    if (root == NULL) {
        return newStudent;
    }
    if (strcmp(newStudent->name, root->name) < 0) {
        root->left = insertStudent(root->left, newStudent);
    } else {
        root->right = insertStudent(root->right, newStudent);
    }
    return root;
}

void inorderTraversal(Student* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("이름: %s, 중간 점수: %d, 기말 점수: %d\n", root->name, root->midterm, root->final);
        inorderTraversal(root->right);
    }
}

Student* searchStudent(Student* root, const char* name) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }
    if (strcmp(name, root->name) < 0) {
        return searchStudent(root->left, name);
    }
    return searchStudent(root->right, name);
}

int main() {
    int n;
    printf("학생 수를 입력하세요: ");
    scanf("%d", &n);

    Student* root = NULL;
    for (int i = 0; i < n; i++) {
        char name[20];
        int midterm, final;
        printf("학생의 이름, 중간 점수, 기말 점수를 입력하세요 %d: ", i + 1);
        scanf("%s %d %d", name, &midterm, &final);
        Student* newStudent = createStudent(name, midterm, final);
        root = insertStudent(root, newStudent);
    }

    // 트리의 루트에서 중위 순회 시작
    printf("\n학생 정보:\n");
    inorderTraversal(root); 

    char searchName[20];
    printf("\n이름을 검색하세요: ");
    scanf("%s", searchName);
    Student* foundStudent = searchStudent(root, searchName);
    if (foundStudent) {
        printf("검색 결과: 이름: %s, 중간 점수: %d, 기말 점수: %d\n", foundStudent->name, foundStudent->midterm, foundStudent->final);
    } else {
        printf("학생의 이름을 찾을 수 없습니다 %s.\n", searchName);
    }

    //동적 메모리 할당 후 해제
    free(root);

    return 0;
}
