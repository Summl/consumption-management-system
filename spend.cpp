#include"spend.h"

//1.录入学生消费信息
void addStudentSpend(){
	printf("----------1.录入学生消费信息----------\n");
	//输入数据到数组
	//月份自增
	maxIndex ++;
	Spends[maxIndex].month = createMonth();
	if(Spends[maxIndex].month>12){
		printf("----------下一年----------\n");
	}
	Spends[maxIndex].month=Spends[maxIndex].month % 12 ;

	//给学生消费信息信息赋值
	printf("请输入季节：");	
	while(1){
		scanf("%s",Spends[maxIndex].season);
		if((strcmp(Spends[maxIndex].season,"春季")!=0) && 
			(strcmp(Spends[maxIndex].season,"夏季")!=0) && 
			(strcmp(Spends[maxIndex].season,"秋季")!=0) && 
			(strcmp(Spends[maxIndex].season,"冬季")!=0)){
				printf("输入错误！请重新输入：\n");
				continue;
		}else if(Spends[maxIndex].month == 12 ||Spends[maxIndex].month == 1 ||Spends[maxIndex].month == 2 ){
			if((strcmp(Spends[maxIndex].season,"冬季")!=0)){
				printf("季节输入错误！当前季节为：冬季\n");
				strcpy(Spends[maxIndex].season,"冬季");break;
			}else{
				break;
			}			
		}else if(Spends[maxIndex].month == 3 ||Spends[maxIndex].month == 4 ||Spends[maxIndex].month == 5){
			if((strcmp(Spends[maxIndex].season,"春季")!=0)){
				printf("季节输入错误！当前季节为：春季\n");
				strcpy(Spends[maxIndex].season,"春季");
				break;
			 }else{
				break;
			}
		}else if(Spends[maxIndex].month == 6 ||Spends[maxIndex].month == 7 ||Spends[maxIndex].month == 8){
			if((strcmp(Spends[maxIndex].season,"夏季")!=0)){
			printf("季节输入错误！当前季节为：夏季\n");
			strcpy(Spends[maxIndex].season,"夏季");
			break;
			}else{
			break;
			}
		}else if(Spends[maxIndex].month == 9 ||Spends[maxIndex].month == 10 ||Spends[maxIndex].month == 11){
			if((strcmp(Spends[maxIndex].season,"秋季")!=0)){
			printf("季节输入错误！当前季节为：秋季\n");
			strcpy(Spends[maxIndex].season,"秋季");
			break;
			}else{
			break;
			}
		}
	}
	printf("请输入吃饭消费：");
	while(1){
		scanf("%d",&Spends[maxIndex].foodSpend);
		if(Spends[maxIndex].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}	
	printf("请输入电话消费：");
	while(1){
		scanf("%d",&Spends[maxIndex].phoneSpend);
		if(Spends[maxIndex].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}		
	printf("请输入买书消费：");
	while(1){
		scanf("%d",&Spends[maxIndex].bookSpend);
		if(Spends[maxIndex].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}		
	printf("请输入其它消费：");
	while(1){
		scanf("%d",&Spends[maxIndex].otherSpend);
		if(Spends[maxIndex].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}
	printf("请输入勤工俭学收入：");
	while(1){
		scanf("%d",&Spends[maxIndex].workStudyIncome);
		if(Spends[maxIndex].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}
	//计算月总支出
	Spends[maxIndex].totalSpend =
		Spends[maxIndex].foodSpend +
		Spends[maxIndex].phoneSpend +
		Spends[maxIndex].bookSpend +
		Spends[maxIndex].otherSpend;
	//状态默认置为1
	Spends[maxIndex].state = 1;
	//写文件
	if(writeData() == 1){
		printf("增加成功！\n");
	}else{
		printf("增加失败！\n");
	}
}

//2.删除学生的消费信息，学生回家了或这个月不想被记录
//函数功能：删除学生信息，将学生状态置为0
//参数：无
//返回值：无
void deleteStudentSpend(){
	printf("----------2.删除学生的消费信息----------\n");
	int month;
	int index = -1;
	int answer = 0;
	printf("请输入要删除消费的月份：");
	scanf("%d",&month);
	//根据月份查找
	index = findIndex(month);
	if(index == -1){
		printf("没有该月份的消费信息！\n");
		return;//当前函数结束，后续程序不再执行，返回被调用处
	}
	//如果找到，打印当前学生消费信息
	printCurrentSpend(index);
	printf("您确定要删除吗？1.是  2.否：");
	scanf("%d",&answer);
	if(answer == 1){
		//当前学生是否在校的状态置为0
		Spends[index].state = 0;
		//重新写文件
		if(writeData() == 1){
			printf("删除成功！\n");
		}else{
			printf("删除失败！\n");
		}
	}
}

//根据月份查找
void queryByMonth(){
	int month;
	int index = -1;
	printf("请输入月份：");
	scanf("%d",&month);
	index = findIndex(month);
	if(index == -1){
		printf("没有该月的消费信息！\n");
		return;
	}
	//如果找到，打印学生的消费信息
	printCurrentSpend(index);
}

//函数功能：根据季节查找学生消费信息
//参数：无
//返回值：无
void queryBySeason(){
	char season[6];
	int index = -1;
	int flag = 0;
	printf("请输入季节：");
	scanf("%s",&season);
	//遍历数组
	for(int  i = 0; i <= maxIndex; i++){
		if(Spends[i].state == 1){
			if(strstr(Spends[i].season,season) != NULL){
				flag = 1;
				printCurrentSpend(i);
			}
		}
	}
	if(flag == 0){
		printf("没有该季节的消费信息！\n");
	}
}

//3.查找学生的消费信息
//函数功能：查询学生的消费信息，可以根据月份或季节查询
//参数：无
//返回值：无
void searchStudentSpend(){
	printf("----------3.查找学生的消费信息----------\n");
	int select = 0;
	printf("  1.按月份查询  2.按季节查询  \n");
	scanf("%d",&select);
	if(select == 1){
		//按月份查找
		queryByMonth();
	}else{
		//按季节查找
		queryBySeason();
	}
}

//4.修改学生的消费信息
//函数功能：修改学生的消费信息，先根据月份查找
//找到后重新输入学生的消费数据，然后再写文件
//参数：无
//返回值：无
void updateStudentSpend(){
	printf("----------4.修改学生的消费信息----------\n");
	int month;
	int index = -1;
	printf("请输入要修改的月份：");
	scanf("%d",&month);
	//根据月份查找学生的消费信息
	index = findIndex(month);
	if(index == -1){
		printf("没有该月份的消费信息！\n");
		return;//当前函数结束，后续程序不再执行，返回被调用处
	}
	//如果找到，打印当前学生的消费信息
	printCurrentSpend(index);
	//重新输入学生的消费信息
	printf("请输入消费所处的季节：");
	while(1){
		scanf("%s",Spends[index].season);
		if((strcmp(Spends[index].season,"春季")!=0) && 
			(strcmp(Spends[index].season,"夏季")!=0) && 
			(strcmp(Spends[index].season,"秋季")!=0) && 
			(strcmp(Spends[index].season,"冬季")!=0)){
				printf("输入错误！请重新输入：\n");
				continue;
		}else if(Spends[index].month == 12 ||Spends[index].month == 1 ||Spends[index].month == 2 ){
			if((strcmp(Spends[index].season,"冬季")!=0)){
				printf("季节输入错误！当前季节为：冬季\n");
				strcpy(Spends[index].season,"冬季");break;
			}else{
				break;
			}			
		    }else if(Spends[index].month == 3 ||Spends[index].month == 4 ||Spends[index].month == 5){
			if((strcmp(Spends[index].season,"春季")!=0)){
				printf("季节输入错误！当前季节为：春季\n");
				strcpy(Spends[index].season,"春季");
				break;
			 }else{
				break;
			}
		    }else if(Spends[index].month == 6 ||Spends[index].month == 7 ||Spends[index].month == 8){
			if((strcmp(Spends[index].season,"夏季")!=0)){
			printf("季节输入错误！当前季节为：夏季\n");
			strcpy(Spends[index].season,"夏季");
			break;
			}else{
			break;
			}
			}else if(Spends[index].month == 9 ||Spends[index].month == 10 ||Spends[index].month == 11){
			if((strcmp(Spends[index].season,"秋季")!=0)){
			printf("季节输入错误！当前季节为：秋季\n");
			strcpy(Spends[index].season,"秋季");
			break;
			}else{
			break;
			}
		}
	}
	printf("请输入吃饭消费：");
	while(1){
		scanf("%d",&Spends[index].foodSpend);
		if(Spends[index].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}
	printf("请输入电话消费：");
	while(1){
		scanf("%d",&Spends[index].phoneSpend);
		if(Spends[index].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}		
	printf("请输入买书消费：");
	while(1){
		scanf("%d",&Spends[index].bookSpend);
		if(Spends[index].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}		
	printf("请输入其它消费：");
	while(1){
		scanf("%d",&Spends[index].otherSpend);
		if(Spends[index].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}
	printf("请输入勤工俭学收入：");
	while(1){
		scanf("%d",&Spends[index].workStudyIncome);
		if(Spends[index].foodSpend<0){
			printf("输入错误！请重新输入：\n");
			continue;
		}else{
			break;
		}
	}
	//计算月总支出
	Spends[index].totalSpend =
		Spends[index].foodSpend +
		Spends[index].phoneSpend +
		Spends[index].foodSpend +
		Spends[index].otherSpend;
	//重新写文件
	if(writeData() == 1){
		printf("修改成功！\n");
	}else{
		printf("修改失败！\n");
	}
}

//5.打印学生的消费信息
//函数功能：打印数组中实际存在的学生的消费信息
//参数：无
//返回值：无
void printfStudentSpend(){
	printf("----------5.打印学生的消费信息----------\n");
	printf("|---------------------------------------------------------------------------|\n");
	printf("|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-12s|%-8s|\n",
		"月份","季节","吃饭消费","电话消费","买书消费","其它消费","勤工俭学收入","月总支出");
	printf("|--------+--------+--------+--------+--------+--------+------------+--------|\n");
	for(int i = 0; i<= maxIndex; i++){
		if(Spends[i].state == 1){
			printf("|%-8d|%-8s|%-8d|%-8d|%-8d|%-8d|%-12d|%-8d|\n",
				Spends[i].month,
				Spends[i].season,
				Spends[i].foodSpend,
				Spends[i].phoneSpend,
				Spends[i].bookSpend,
				Spends[i].otherSpend,
				Spends[i].workStudyIncome,
				Spends[i].totalSpend);
			if(i < maxIndex){
				printf("|--------+--------+--------+--------+--------+--------+------------+--------|\n");
			}else{
				printf("|---------------------------------------------------------------------------|\n");
			}
		}
	}
}

//计算各消费的最大值
void getMaxSpend()
{
	int maxfoodSpend = Spends[0].foodSpend;
	int maxphoneSpend = Spends[0].phoneSpend;
	int maxbookSpend = Spends[0].bookSpend;
	int maxotherSpend = Spends[0].otherSpend;
	int maxworkStudyIncome = Spends[0].workStudyIncome;
	int i = 0;
	int foodSpendIndex = 0;
	int phoneSpendIndex = 0;
	int bookSpendIndex = 0;
	int otherSpendIndex = 0;
	int workStudyIncomeIndex = 0;

	for(i=1 ;i<=maxIndex; i++){
		if(Spends[i].state ==1)
		{
			if(maxfoodSpend < Spends[i].foodSpend)
			{
				maxfoodSpend = Spends[i].foodSpend;
				foodSpendIndex = i;	
			}
			if(maxphoneSpend < Spends[i].phoneSpend)
			{
				maxphoneSpend = Spends[i].phoneSpend;
				phoneSpendIndex = i;	
			}
			if(maxbookSpend < Spends[i].bookSpend)
			{
				maxbookSpend = Spends[i].bookSpend;
				bookSpendIndex = i;	
			}
			if(maxotherSpend < Spends[i].otherSpend)
			{
				maxotherSpend = Spends[i].otherSpend;
				otherSpendIndex = i;	
			}
			if(maxworkStudyIncome < Spends[i].workStudyIncome)
			{
				maxworkStudyIncome = Spends[i].workStudyIncome;
				workStudyIncomeIndex = i;	
			}

		}

	}
	printf("吃饭消费最高： %d\n",maxfoodSpend);
	printCurrentSpend(foodSpendIndex);
	printf("电话消费最高： %d\n",maxphoneSpend);
	printCurrentSpend(phoneSpendIndex);
	printf("买书消费最高： %d\n",maxbookSpend);
	printCurrentSpend(bookSpendIndex);
	printf("其它消费最高： %d\n",maxotherSpend);
	printCurrentSpend(otherSpendIndex);
	printf("****************************************************************************\n");
	printf("勤工俭学收入最高： %d\n",maxworkStudyIncome);
	printCurrentSpend(workStudyIncomeIndex);
}

//计算各消费的平均值
void getAvgSpend()
{
	double avgfoodSpend = 0;
	double avgphoneSpend = 0;
	double avgbookSpend = 0;
	double avgotherSpend = 0;
	double avgworkStudyIncome=0;
	int i = 0;
	int count = 0; //实际月份个数 
	for(i = 0; i <= maxIndex; i++)
	{
		if(Spends[i].state == 1)
		{
			avgfoodSpend += Spends[i].foodSpend;
			avgphoneSpend += Spends[i].phoneSpend;
			avgbookSpend += Spends[i].bookSpend;
			avgotherSpend += Spends[i].otherSpend;
			avgworkStudyIncome += Spends[i].workStudyIncome;
			count++;
		}
	}
	printf("|-----------------------|\n");
	printf("|%-14s| %-7.2lf|\n","吃饭消费平均:",avgfoodSpend/count);
	printf("|--------------+--------|\n");
	printf("|%-14s| %-7.2lf|\n","电话消费平均:",avgphoneSpend/count);
	printf("|--------------+--------|\n");
	printf("|%-14s| %-7.2lf|\n","买书消费平均",avgbookSpend/count);
	printf("|-----------------------|\n");
	printf("|%-14s| %-7.2lf|\n","其他消费平均",avgotherSpend/count);
	printf("|-----------------------|\n");
    printf("|*************************|\n");
	printf("|-------------------------|\n");
	printf("|%-14s| %-7.2lf|\n","勤工俭学收入平均",avgworkStudyIncome/count);
	printf("|-------------------------|\n");
} 

//6.学生消费信息分析
void analysisSyudentSpend(){
	printf("----------6.统计学生消费信息----------\n");
	printf("-----学生消费、收入分别最高：\n");
	getMaxSpend();
	printf("------学生消费、收入分别平均：\n");
	getAvgSpend();
}


//辅助业务
//7.读文件
//函数功能：将磁盘上的数据读取到数组中,只在程序启动时读一次
//参数：无
//返回值：返回读取到数组的最大索引，如果是第一次运行，
//需要创建文件并返回-1
int readData(){
	//定义读取文件的行数
	int i = 0;
	//7.1.打开文件
	if((fp = fopen("studentSpendInfo.txt","r")) == NULL){
		//创建新文件
		fp = fopen("studentSpendInfo.txt","w");
		return -1;
	}
	//7.2.读文件
	while (!feof(fp)){
		fscanf(fp,"%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d",
			&Spends[i].month,
			Spends[i].season,
			&Spends[i].foodSpend,
			&Spends[i].phoneSpend,
			&Spends[i].bookSpend,
			&Spends[i].otherSpend,
			&Spends[i].workStudyIncome,
			&Spends[i].totalSpend,
			&Spends[i].state);
		//读取一行数据，索引+1
		i++;
	}
	//7.3.关闭文件
	fclose(fp);
	//多读取一行，索引从0开始
	return i-2;
}

//8.写文件
//函数功能：将数组中的数据写到磁盘上的文件中，
//增删改查操作都需要进行写文件
//参数：无
//返回值：写文件成功返回1，失败返回0
int writeData(){
	//数组索引
	int i = 0;
	//8.1.打开文件
	if((fp = fopen("studentSpendInfo.txt","w"))==NULL){
		printf("打开文件失败！\n");
		return 0;
	}
	//8.2.写文件
	for(i = 0; i <= maxIndex; i++ ){
		fprintf(fp,"%d\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
			Spends[i].month,
			Spends[i].season,
			Spends[i].foodSpend,
			Spends[i].phoneSpend,
			Spends[i].bookSpend,
			Spends[i].otherSpend,
			Spends[i].workStudyIncome,
			Spends[i].totalSpend,
			Spends[i].state);
	}
	//8.3关闭文件
	fclose(fp);
	return 1;
}

//9.自动生成月份
//函数功能：自动生成月份：如果是1月，月份是1，否则返回上一月+1
//参数：无
//返回值：月份
int createMonth(){
	if(maxIndex == 0){
		return 1;
	}else{//返回上一月+1
		return Spends[maxIndex-1].month + 1;
	}
}

//10.根据月份查找索引
//函数功能：根据月份查询学生的消费信息在数组中的索引位置
//参数：月份
//返回值：该学生的消费信息在数组中的索引，如果找到了返回索引，
//如果没找到，返回-1
int findIndex(int month){
	int index = -1;
	for(int i = 0; i <= maxIndex; i++){
		//保证学生在校状态正常
		if(Spends[i].state == 1){
			if(Spends[i].month == month){
				//记录当前索引
				index = i;
				break;
			}
		}		
	}
	return index;
}

//11.显示当前学生的消费信息
//函数功能：打印当前索引的学生的消费信息
//参数：数组中的索引
//返回值：无
void printCurrentSpend(int index){
	printf("|---------------------------------------------------------------------------|\n");
	printf("|%-8s|%-8s|%-8s|%-8s|%-8s|%-8s|%-12s|%-8s|\n",
		"月份","季节","吃饭消费","电话消费","买书消费","其它消费","勤工俭学收入","月总支出");
	printf("|--------+--------+--------+--------+--------+--------+------------+--------|\n");
	printf("|%-8d|%-8s|%-8d|%-8d|%-8d|%-8d|%-12d|%-8d|\n",
		Spends[index].month,
		Spends[index].season,
		Spends[index].foodSpend,
		Spends[index].phoneSpend,
		Spends[index].bookSpend,
		Spends[index].otherSpend,
		Spends[index].workStudyIncome,
		Spends[index].totalSpend);
	printf("|---------------------------------------------------------------------------|\n");
}

//12.欢迎界面
int welcome(int y){
	//int y;
	printf("----------------------------------------\n");
	printf("  欢迎使用");
	printf("%d",y);
	printf("年大学生个人消费管理系统   \n");
	printf("----------------------------------------\n");
	printf("\n");
	return 0;
}

//13.主菜单
void mainMenu(){
	//循环显示
	int select = 0;//定义选择
	while(true){
		printf("----------------------------------------\n");
		printf("          1.录入学生的消费信息          \n");
		printf("          2.删除学生的消费信息          \n");
		printf("          3.查找学生的消费信息          \n");
		printf("          4.修改学生的消费信息          \n");
		printf("          5.打印学生的消费信息          \n");
		printf("          6.统计学生的消费信息          \n");
		printf("          0.退出系统                    \n");
		printf("----------------------------------------\n");
		printf("请输入您的选择：\n");
		scanf("%d",&select);
		switch(select)
		{
		case 1://1.录入学生的消费信息
			addStudentSpend();
			break;
		case 2://2.删除学生的消费信息
			deleteStudentSpend();
			break;
		case 3://3.查找学生的消费信息
			searchStudentSpend();
			break;
		case 4://4.修改学生的消费信息
			updateStudentSpend();
			break;
		case 5://5.打印学生的消费信息
			printfStudentSpend();
			break;
		case 6://6.学生的消费信息分析
			analysisSyudentSpend();
			break;
		case 0://0.退出系统
			exit(0);
		default:
			printf("您的选择有误，请重新选择！\n");
		}
	}
}

//主函数
void main()
{
	int year;
	printf("请输入您想记录的消费的年份：");
	scanf("%d",&year);
	printf("%d",year);
	printf("年大学生消费记录：\n");
	welcome(year);
	maxIndex = readData();
	mainMenu();
	system("pause");
}



