#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct teacher_load {
    int *idx;
    float *credit;
};

static void bubble_sort(int *idx, float *credit, int n) {
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (credit[j]>credit[j+1]) {
                float temp_cr=credit[j];
                credit[j]=credit[j+1];
                credit[j+1]=temp_cr;

                int temp_idx=idx[j];
                idx[j]=idx[j+1];
                idx[j+1]=temp_idx;
            }
        }
    }
}

static char* remove_edge_spaces(const char *s) {
     static char s_new[500];
     int len=strlen(s);
     int iter=0,f=0,l=0;
     for (int i=0; i<len; i++) {
         if (s[i]!=' ' && s[i]!='\t' && s[i]!='\n' && s[i]!='\r') {
             f=i;
             break;
         }
     }
    for (int i=len-1; i>=0; i--) {
         if (s[i]!=' ' && s[i]!='\t' && s[i]!='\n' && s[i]!='\r') {
             l=i;
             break;
         }
    }
    for (int i=f; i<=l; i++) {
        s_new[iter++]=s[i];
    }
    s_new[iter]='\0';
    return s_new;
 }

static int get_num(const char *s) {
    int len=strlen(s);
    char dig[10];
    int iter=0;
    for (int i=0; i<len; i++) {
        if (s[i]>=48 && s[i]<=57)
            dig[iter++]=s[i];
    }
    dig[iter]='\0';
    return atoi(dig);
}
int main() {
    FILE *p1= fopen("C:/Users/Rifat/OneDrive/Documents/routine_project/new_input1.txt","r");
    if (!p1)
        return 1;
    int total_course=0;
    int theory=0, sessional=0;
    int done_assistant=0, done_associate=0, done_professor=0;
    char line[1000];
    while (fgets(line,sizeof(line),p1)!=NULL) {
        total_course++;
    }
    rewind(p1);

    char course_name[total_course][200], course_no[total_course][20];
    float available_course_cr[total_course];
    int line_no=0;
    while (fgets(line,sizeof(line),p1)!=NULL) {
        int first=0, second=0;
        int len= strlen(line);
        for (int i=0; i<len; i++) {
            if (line[i]=='|' && first==0) {
                first=i;
                int iter=0;
                for (int j=0; j<first; j++) {
                    course_no[line_no][iter++]=line[j];
                }
                course_no[line_no][iter]='\0';
            }
            if (line[i]=='|' && first!=0) {
                int iter=0;
                second=i;
                for (int j=first+2; j<second; j++) {
                    course_name[line_no][iter++]=line[j];
                }
                course_name[line_no][iter]='\0';
            }
        }
        if (second!=0) {
            int iter=0;
            char credit[10];
            for (int j=second+2; j<len; j++) {
                if (line[j]!=' ' && line[j]!='\n') {
                    credit[iter++]=line[j];
                }
            }
            credit[iter]='\0';
            available_course_cr[line_no]=atof(credit);
        }
        line_no++;
    }
    for (int i=0; i<total_course; i++) {
        const int len_no=strlen(course_no[i]);
        char dig[10];
        int iter=0;
        for (int j=0; j<len_no; j++) {
            if (course_no[i][j]>=48 && course_no[i][j]<=57) {
                dig[iter++]=course_no[i][j];
            }
        }
        dig[iter]='\0';
        const int digit=atoi(dig);
        if (digit%2)
            theory++;
        else
            sessional++;
    }
    // for (int i=0; i<40; i++) {
    //     printf("%.2f\n",credit_hour[i]);
    // }
    // for (int i=0; i<40; i++) {
    //     printf("%s\n",course_no[i]);
    // }
    // for (int i=0; i<40; i++) {
    //     printf("%s\n",course_name[i]);
    // }
    FILE *p2= fopen("C:/Users/Rifat/OneDrive/Documents/routine_project/input2.txt","r");
    if (!p2) {
        fclose(p1);
        return 1;
    }
    int total_type=0;
    while (fgets(line,sizeof(line),p2)!=NULL) {
        total_type++;
    }
    rewind(p2);
    char teacher_type[total_type][50];
    float max_cr[total_type];
    int line2=0;
    while (fgets(line,sizeof(line),p2)!=NULL) {
        int first=0;
        int len= strlen(line);
        int iter=0;
        for (int i=0; i<len; i++) {
            if (line[i]=='|' && first==0) {
                first=i;
                for (int j=0; j<first; j++) {
                    teacher_type[line2][iter++]=line[j];
                }
                teacher_type[line2][iter]='\0';
            }
            if (first!=0) {
                char val[10];
                iter=0;
                for (int j=first+2; j<len; j++) {
                    if (line[j]=='\n')
                        continue;
                    val[iter++]=line[j];
                }
                val[iter]='\0';
                float value= atof(val);
                max_cr[line2]=value;
                break;
            }
        }
        line2++;
    }
    // for (int i=0; i<5; i++) {
    //     printf("%.2f\n",max_cr[i]);
    // }
    // for (int i=0; i<5; i++) {
    //     printf("%s\n",teacher_type[i]);
    // }
    FILE *p3=fopen("C:/Users/Rifat/OneDrive/Documents/routine_project/input3.txt","r");
    if (!p3) {
        fclose(p1);
        fclose(p2);
        return 1;
    }
    int total_teacher=0;
    while (fgets(line,sizeof(line),p3)!=NULL) {
        total_teacher++;
    }
    rewind(p3);
    char status[total_teacher][50];
    char name[total_teacher][100];
    for (int i=0; fgets(line,sizeof(line),p3)!=NULL; i++) {
        int len=strlen(line);
        int idx=0;
        for (int j=0; j<len; j++) {
            if (line[j]=='|') {
                idx=j;
                break;
            }
        }
        int iter=0;
        for (int j=0; j<idx; j++) {
            name[i][iter++]=line[j];
        }
        name[i][iter]='\0';
        iter=0;
        for (int j=idx+2; j<len; j++) {
            if (line[j]=='\n')
                continue;
            status[i][iter++]=line[j];
        }
        status[i][iter]='\0';
    }
    // for (int i=0; i<41; i++) {
    //     printf("%s\n",name[i]);
    // }
    // for (int i=0; i<41; i++) {
    //     printf("%s\n",status[i]);
    // }
    // printf("%s\n",status[25]);
    float available_teacher_cr[total_teacher];
    for (int i=0; i<total_teacher; i++) {
        char current_status[50];
        strcpy(current_status,remove_edge_spaces(status[i]));
        for (int j=0; j<total_type; j++) {
            char current_type[50];
            strcpy(current_type,remove_edge_spaces(teacher_type[j]));
            if (!strcmp(current_status,current_type)) {
                available_teacher_cr[i]=max_cr[j];
                break;
            }
        }
    }
    // for (int i=0; i<total_teacher; i++) {
    //     printf("%.2f\n",available_teacher_cr[i]);
    // }
    int type_cnt[total_type];
    for (int i=0; i<total_type; i++) {
        type_cnt[i]=0;
    }
    for (int i=0; i<total_teacher; i++) {
        char current_status[50];
        strcpy(current_status,remove_edge_spaces(status[i]));
        for (int j=0; j<total_type; j++) {
            char current_type[50];
            strcpy(current_type,remove_edge_spaces(teacher_type[j]));
            if (!strcmp(current_status,current_type)) {
                type_cnt[j]++;
            }
        }
    }
    // for (int i=0; i<total_type; i++) {
    //     printf("%d\n",type_cnt[i]);
    // }

    int assigned_cnt[total_teacher];
    for (int i=0; i<total_teacher; i++) {
        assigned_cnt[i]=0;
    }
    char assigned_course_no_s[total_teacher][100];
    int iter[total_teacher];
    for (int i=0; i<total_teacher; i++) {
        iter[i]=0;
    }

    int total_professor=0;
    for (int i=0; i<total_type; i++) {
        char sts[30];
        strcpy(sts,remove_edge_spaces(teacher_type[i]));
        for (int j=0; j<total_teacher; j++) {
            if (!strcmp(sts,"Professor")) {
                total_professor++;
            }
            else if (!strcmp(sts,"Associate Professor")) {
                total_professor++;
            }
            else if (!strcmp(sts,"Assistant Professor")) {
                total_professor++;
            }
        }
    }

    // for (int i=0; i<total_teacher; i++) {
    //     printf("%.2f   ",available_teacher_cr[10]);
    // }
    // printf("%.2f",max_cr[3]);

    // thesis er ta
    int thesis_idx;
    for (int i=0; i<total_course; i++) {
        int nm= get_num(course_no[i]);
        if (nm==400) {
            thesis_idx=i;
        }
    }
    // printf("%d\n",thesis_idx);
    // printf("%.2f\n",available_course_cr[thesis_idx]);
    int index;
    for (int ii=0; ii<total_type; ii++) {
        char __status[50];
        strcpy(__status,remove_edge_spaces(teacher_type[ii]));
        if (!strcmp(__status,"Professor"))
            index=ii;
    }
    // printf("%d\n",type_cnt[index]);
    for (int ij=0; ij<type_cnt[index]; ij++) {
        struct teacher_load t;
        t.idx=malloc(sizeof(int)*type_cnt[index]);
        t.credit=malloc(sizeof(float)*type_cnt[index]);

        int iterator=0;
        for (int ii=0; ii<total_teacher; ii++) {
            char __status[50];
            strcpy(__status,remove_edge_spaces(status[ii]));
            if (!strcmp(__status,"Professor")) {
                t.idx[iterator]=ii;
                t.credit[iterator]=max_cr[index]-available_teacher_cr[ii];
                iterator++;
            }
        }
        bubble_sort(t.idx,t.credit,type_cnt[index]);
        // for (int ii=0; ii<17; ii++) {
        //     printf("%d %.2f\n",t.idx[ii],t.credit[ii]);
        // }

        if (available_teacher_cr[t.idx[0]]>=available_course_cr[thesis_idx]) {
            available_teacher_cr[t.idx[0]]-=available_course_cr[thesis_idx];
            // printf("%.2f\n",available_course_cr[thesis_idx]);
            // printf("%.2f\n",available_teacher_cr[t.idx[0]]);
            // available_course_cr[i]=0;
            // printf("%.2f\n",6.00-3.00);
            assigned_cnt[t.idx[0]]++;
            char s_num[10]="400";
            int len_s_num=strlen(s_num);
            for (int k=0; k<len_s_num; k++) {
                assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
            }
            assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
        }
        free(t.idx);
        free(t.credit);
    }


    for (int ii=0; ii<total_type; ii++) {
        char __status[50];
        strcpy(__status,remove_edge_spaces(teacher_type[ii]));
        if (!strcmp(__status,"Assistant Professor"))
            index=ii;
    }

    // printf("%d\n",type_cnt[index]);
    for (int ij=0; ij<type_cnt[index]; ij++) {
        struct teacher_load t;
        t.idx=malloc(sizeof(int)*type_cnt[index]);
        t.credit=malloc(sizeof(float)*type_cnt[index]);

        int iterator=0;
        for (int ii=0; ii<total_teacher; ii++) {
            char __status[50];
            strcpy(__status,remove_edge_spaces(status[ii]));
            if (!strcmp(__status,"Assistant Professor")) {
                t.idx[iterator]=ii;
                t.credit[iterator]=max_cr[index]-available_teacher_cr[ii];
                iterator++;
            }
        }
        bubble_sort(t.idx,t.credit,type_cnt[index]);
        // for (int ii=0; ii<17; ii++) {
        //     printf("%d %.2f\n",t.idx[ii],t.credit[ii]);
        // }

        if (available_teacher_cr[t.idx[0]]>=available_course_cr[thesis_idx]) {
            available_teacher_cr[t.idx[0]]-=available_course_cr[thesis_idx];
            //available_course_cr[i]=0;
            assigned_cnt[t.idx[0]]++;
            char s_num[10]="400";
            int len_s_num=strlen(s_num);
            for (int k=0; k<len_s_num; k++) {
                assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
            }
            assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
        }
        free(t.idx);
        free(t.credit);
    }

    for (int ii=0; ii<total_type; ii++) {
        char __status[50];
        strcpy(__status,remove_edge_spaces(teacher_type[ii]));
        if (!strcmp(__status,"Associate Professor"))
            index=ii;
    }

    for (int ij=0; ij<type_cnt[index]; ij++) {
        struct teacher_load t;
        t.idx=malloc(sizeof(int)*type_cnt[index]);
        t.credit=malloc(sizeof(float)*type_cnt[index]);

        int iterator=0;
        for (int ii=0; ii<total_teacher; ii++) {
            char __status[50];
            strcpy(__status,remove_edge_spaces(status[ii]));
            if (!strcmp(__status,"Associate Professor")) {
                t.idx[iterator]=ii;
                t.credit[iterator]=max_cr[index]-available_teacher_cr[ii];
                iterator++;
            }
        }
        bubble_sort(t.idx,t.credit,type_cnt[index]);
        // for (int ii=0; ii<17; ii++) {
        //     printf("%d %.2f\n",t.idx[ii],t.credit[ii]);
        // }

        if (available_teacher_cr[t.idx[0]]>=available_course_cr[thesis_idx]) {
            available_teacher_cr[t.idx[0]]-=available_course_cr[thesis_idx];
            //available_course_cr[i]=0;
            assigned_cnt[t.idx[0]]++;
            char s_num[10];
            sprintf(s_num,"%d",400);
            int len_s_num=strlen(s_num);
            for (int k=0; k<len_s_num; k++) {
                assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
            }
            assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
        }
        free(t.idx);
        free(t.credit);
    }
    //printf("i=25 er %d\n",iter[25]);
    // for (int ii=0; ii<type_cnt[1]; ii++) {
    //     printf("%.2f\n",available_teacher_cr[ii]);
    // }

    // main allocation
    for (int i=0; i<total_course; i++) {
        if (available_course_cr[i]==0)
            continue;

        int num=get_num(course_no[i]);
        if (num%2==0 && num!=400) {
            // Here we are finding the index of lecturer so that we can make array
            // by allocating dynamic memory
            for (int ii=0; ii<total_type; ii++) {
                char __status[50];
                strcpy(__status,remove_edge_spaces(teacher_type[ii]));
                if (!strcmp(__status,"Lecturer"))
                    index=ii;
            }

            struct teacher_load t;
            t.idx=malloc(sizeof(int)*type_cnt[index]);
            t.credit=malloc(sizeof(float)*type_cnt[index]);

            int iterator=0;
            for (int ii=0; ii<total_teacher; ii++) {
                char __status[50];
                strcpy(__status,remove_edge_spaces(status[ii]));
                if (!strcmp(__status,"Lecturer")) {
                    t.idx[iterator]=ii;
                    t.credit[iterator]=max_cr[index]-available_teacher_cr[ii];
                    iterator++;
                }
            }
            bubble_sort(t.idx,t.credit,type_cnt[index]);
            // for (int ii=0; ii<12; ii++) {
            //     printf("%d %.2f\n",t1.idx[ii],t1.credit[ii]);
            // }

            if (available_teacher_cr[t.idx[0]]>=available_course_cr[i]) {
                available_teacher_cr[t.idx[0]]-=available_course_cr[i];
                available_course_cr[i]=0;
                assigned_cnt[t.idx[0]]++;
                char s_num[10];
                sprintf(s_num,"%d",num);
                int len_s_num=strlen(s_num);
                for (int k=0; k<len_s_num; k++) {
                    assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
                }
                assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
            }

            free(t.idx);
            free(t.credit);
        }

        else if (num==400) {
            available_course_cr[thesis_idx]=0;
        }

        else {
            // if (num==249) {
            //     printf("hello");
            //     printf("%d %d %d\n",done_assistant,done_associate,done_professor);
            // }
            // printf("i=25 er %d\n",iter[25]);
            if (!done_assistant) {
                //printf("hello");
                for (int ii=0; ii<total_type; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(teacher_type[ii]));
                    if (!strcmp(__status,"Assistant Professor"))
                        index=ii;
                }
                int idx_assistant[type_cnt[index]];
                int it=0;
                for (int ii=0; ii<total_teacher; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(status[ii]));
                    if (!strcmp(__status,"Assistant Professor"))
                        idx_assistant[it++]=ii;
                }

                struct teacher_load t;
                t.idx=malloc(sizeof(int)*type_cnt[index]);
                t.credit=malloc(sizeof(float)*type_cnt[index]);

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.idx[ii]=idx_assistant[ii];
                }

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.credit[ii]=max_cr[index]-available_teacher_cr[t.idx[ii]];
                }
                bubble_sort(t.idx,t.credit,type_cnt[index]);

                // for (int ii=0; ii<type_cnt[index]; ii++) {
                //     printf("%.2f\n",available_teacher_cr[ii]);
                // }
                if (available_teacher_cr[t.idx[0]]>=available_course_cr[i]) {
                    available_teacher_cr[t.idx[0]]-=available_course_cr[i];
                    available_course_cr[i]=0;
                    assigned_cnt[t.idx[0]]++;
                    char s_num[10];
                    sprintf(s_num,"%d",num);
                    int len_s_num=strlen(s_num);
                    for (int k=0; k<len_s_num; k++) {
                        assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
                        // printf("hello");
                    }
                    assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
                }
                else {
                    done_assistant=1;
                    i--;
                    continue;
                }
                free(t.idx);
                free(t.credit);
                //printf("i=25 er %d\n",iter[25]);
            }
            else if (!done_associate) {
                for (int ii=0; ii<total_type; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(teacher_type[ii]));
                    if (!strcmp(__status,"Associate Professor"))
                        index=ii;
                }
                int idx_associate[type_cnt[index]];
                int it=0;
                for (int ii=0; ii<total_teacher; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(status[ii]));
                    if (!strcmp(__status,"Associate Professor"))
                        idx_associate[it++]=ii;
                }

                struct teacher_load t;
                t.idx=malloc(sizeof(int)*type_cnt[index]);
                t.credit=malloc(sizeof(float)*type_cnt[index]);

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.idx[ii]=idx_associate[ii];
                }

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.credit[ii]=max_cr[index]-available_teacher_cr[t.idx[ii]];
                }
                bubble_sort(t.idx,t.credit,type_cnt[index]);

                // for (int ii=0; ii<type_cnt[index]; ii++) {
                //     printf("%.2f\n",available_teacher_cr[ii]);
                // }
                if (available_teacher_cr[t.idx[0]]>=available_course_cr[i]) {
                    available_teacher_cr[t.idx[0]]-=available_course_cr[i];
                    available_course_cr[i]=0;
                    assigned_cnt[t.idx[0]]++;
                    char s_num[10];
                    sprintf(s_num,"%d",num);
                    int len_s_num=strlen(s_num);
                    for (int k=0; k<len_s_num; k++) {
                        assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
                        // printf("hello");
                    }
                    assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
                }
                else {
                    done_associate=1;
                    i--;
                    continue;
                }
                free(t.idx);
                free(t.credit);
            }
            else if (!done_professor) {
                for (int ii=0; ii<total_type; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(teacher_type[ii]));
                    if (!strcmp(__status,"Professor"))
                        index=ii;
                }
                int idx_professor[type_cnt[index]];
                int it=0;
                for (int ii=0; ii<total_teacher; ii++) {
                    char __status[50];
                    strcpy(__status,remove_edge_spaces(status[ii]));
                    if (!strcmp(__status,"Professor"))
                        idx_professor[it++]=ii;
                }

                struct teacher_load t;
                t.idx=malloc(sizeof(int)*type_cnt[index]);
                t.credit=malloc(sizeof(float)*type_cnt[index]);

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.idx[ii]=idx_professor[ii];
                }

                for (int ii=0; ii<type_cnt[index]; ii++) {
                    t.credit[ii]=max_cr[index]-available_teacher_cr[t.idx[ii]];
                }
                bubble_sort(t.idx,t.credit,type_cnt[index]);

                // for (int ii=0; ii<type_cnt[index]; ii++) {
                //     printf("%.2f\n",available_teacher_cr[ii]);
                // }
                // if (num==249)
                //     printf("%.2f\n",available_teacher_cr[t.idx[0]]);

                if (available_teacher_cr[t.idx[0]]>=available_course_cr[i]) {
                    available_teacher_cr[t.idx[0]]-=available_course_cr[i];
                    available_course_cr[i]=0;
                    assigned_cnt[t.idx[0]]++;
                    char s_num[10];
                    sprintf(s_num,"%d",num);
                    int len_s_num=strlen(s_num);
                    for (int k=0; k<len_s_num; k++) {
                        assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
                        // printf("hello");
                    }
                    assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
                }
                else {
                    done_professor=1;
                }
                free(t.idx);
                free(t.credit);
            }
        }
    }

    // printf("%.3f\n",available_course_cr[11]);
    // check all courses are taken or not!! Otherwise give it to part time teacher
    for (int i=0; i<total_course; i++) {
        if (available_course_cr[i]) {
            for (int j=0; j<total_type; j++) {
                char __status[50];
                strcpy(__status,remove_edge_spaces(teacher_type[j]));
                if (!strcmp(__status,"Part Time"))
                    index=j;
            }

            struct teacher_load t;
            t.idx=malloc(sizeof(int)*type_cnt[index]);
            t.credit=malloc(sizeof(float)*type_cnt[index]);

            int it=0;
            for (int ii=0; ii<total_teacher; ii++) {
                char __status[50];
                strcpy(__status,remove_edge_spaces(status[ii]));
                if (!strcmp(__status,"Part Time"))
                    t.idx[it++]=ii;
            }
            for (int ii=0; ii<type_cnt[index]; ii++) {
                t.credit[ii]=max_cr[index]-available_teacher_cr[t.idx[ii]];
            }
            bubble_sort(t.idx,t.credit,type_cnt[index]);

            int num=get_num(course_no[i]);
            if (available_teacher_cr[t.idx[0]]>=available_course_cr[i]) {
                available_teacher_cr[t.idx[0]]-=available_course_cr[i];
                available_course_cr[i]=0;
                assigned_cnt[t.idx[0]]++;
                char s_num[10];
                sprintf(s_num,"%d",num);
                int len_s_num=strlen(s_num);
                for (int k=0; k<len_s_num; k++) {
                    assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]=s_num[k];
                }
                assigned_course_no_s[t.idx[0]][iter[t.idx[0]]++]='|';
            }

            free(t.idx);
            free(t.credit);
        }
    }

    // for (int i=0; i<total_teacher; i++) {
    //     printf("%d\n",assigned_cnt[i]);
    // }
    for (int ii=0; ii<total_teacher; ii++) {
        assigned_course_no_s[ii][iter[ii]]='\0';
    }
    for (int ii=0; ii<total_teacher; ii++) {
        printf("%s\n",assigned_course_no_s[ii]);
    }
    // for (int ii=0; ii<16; ii++) {
    //     printf("%.2f\n",available_teacher_cr[ii]);
    // }

    FILE *fpo=fopen("C:/Users/Rifat/OneDrive/Documents/routine_project/output.txt","w");
    if (!fpo) {
        fclose(p1);
        fclose(p2);
        fclose(p3);
        return 1;
    }
    int shop_160=0;
    for (int i=0; i<total_teacher; i++) {
        int course[assigned_cnt[i]];
        int it=0;
        int prvs=0;
        int len=strlen(assigned_course_no_s[i]);
        for(int j=0; j<len; j++) {
            if (assigned_course_no_s[i][j]=='|') {
                int idx=j;
                char string[100];
                for (int k=prvs; k<idx; k++) {
                    string[k-prvs]=assigned_course_no_s[i][k];
                }
                string[idx-prvs]='\0';
                prvs=idx+1;
                course[it++]=atoi(string);
                // printf("%d\n",atoi(string));
            }
        }
        char assigned_course_name[assigned_cnt[i]][100];
        char assigned_course_no[assigned_cnt[i]][30];
        for (int k=0; k<assigned_cnt[i]; k++) {
            for (int j=0; j<total_course; j++) {
                if (get_num(course_no[j])==course[k]) {
                    if (course[k]==160 && shop_160==0) {
                        char temp[100]="Foundry and Welding Shops                     ";
                        strcpy(assigned_course_name[k],temp);
                        char temp2[30]="SHOP 160";
                        strcpy(assigned_course_no[k],temp2);
                    }
                    else if (course[k]==160 && shop_160) {
                        char temp[100]="Mechanical Engineering Drawing -I             ";
                        strcpy(assigned_course_name[k],temp);
                        char temp2[30]="ME 160";
                        strcpy(assigned_course_no[k],temp2);
                    }
                    else {
                        strcpy(assigned_course_name[k],course_name[j]);
                        strcpy(assigned_course_no[k],course_no[j]);
                    }
                }
            }
        }
        for (int j=0; j<assigned_cnt[i]; j++) {
            if (j==0) {
                //printf("%s\t%d\t%s\n",name[i],assigned_cnt[i],assigned_course_name[j]);
                fprintf(fpo,"%s\t\t%d\t\t%s\t%s\n",name[i],assigned_cnt[i],
                    assigned_course_name[j],assigned_course_no[j]);
            }
            else {
                //printf("\t\t\t\t\t%s\n",assigned_course_name[j]);
                fprintf(fpo,"\t\t\t\t\t\t\t\t\t\t\t%s\t%s\n",
                    assigned_course_name[j],assigned_course_no[j]);
            }
        }
        // printf("---------------------------------------------------------------------------"
        //        "--------------------\n");
        fprintf(fpo,"---------------------------------------------------------------------------"
               "-------------------------------------\n");
    }

    fclose(p1);
    fclose(p2);
    fclose(p3);
    return 0;
}