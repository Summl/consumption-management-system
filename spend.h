#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/*功能描述：设计一个大学生个人消费管理系统，主要实现对大学生每月的各项花费进行管理，
	包括消费记录的录入、修改、查询、删除、排序、统计和浏览的功能。
	花费主要包括吃饭消费、电话话费、买书花费、旅游花费、其它花费、勤工俭学收入、月总支出等。*/
	
struct Student{//主结构体
	int month;//月份
	char season[6];//季节
	int foodSpend;//吃饭消费
	int phoneSpend;//电话消费
	int bookSpend;//买书消费
	int otherSpend;//其它消费
	int workStudyIncome;//勤工俭学收入
	int totalSpend;//月总支出
	int state;//状态--学生是否想在校记录消费：1记录 0不记录（可能不在学校）
};

//定义结构体数组存储学生消费信息
struct Student Spends[20];

//定义文件指针，操作文件
FILE *fp;

//定义存储当前的最大索引
int maxIndex = -1;
//函数声明
//主业务
//1.录入学生消费信息
void addStudentSpend();
//2.删除学生消费信息
void deleteStudentSpend();
//3.查找学生消费信息
void searchStudentSpend();
//4.修改学生消费信息
void updateStudentSpend();
void queryByMonth();
void queryBySeason();
//void queryByName();
//5.打印学生消费信息
void printfStudentSpend();
//6.学生消费分析
void analysisSyudentSpend();
void getMaxSpend();
void getAvgSpend();
//辅助业务
//7.读文件
int readData();
//8.写文件
int writeData();
//9.自动生成月份
int createMonth();
//10.根据月份查找索引
int findIndex(int month);
//11.显示当前学生消费信息
void printCurrentSpend(int index);
//12.欢迎界面
int welcome();
//13.主菜单
void mainMenu();