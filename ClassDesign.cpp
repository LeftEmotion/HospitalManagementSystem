#include<bits/stdc++.h>
using namespace std;
int Dcnt = 10000;//10000-10029 医生ID分配
int Pcnt = 20001;//患者ID分配
int Rcnt = 0;//科室分配
int val = 0;//医院收入
int mi_money[10]={1,12,3,5,2,6,7,2,1,4} ;//药品单价，角标为药品ID
int RoomSelete[18] = {101,102,103,104,105,106,107,108,109,201,202,203,204,205,207,208,209};//科室分配顺序
int WeekNum[8];//记录每天挂号数量
char *DoctorName[30]={"克劳德","蒂法","爱丽丝","莱克斯","焰","光","尼亚","齐格","菜月昴","艾米莉亚","帕克","奥托",
"尤里乌斯","莱茵哈鲁特","蕾姆","拉姆","加菲尔","琉兹","罗兹瓦尔","杰乌斯","福尔图娜","贝蒂","佩特拉","撒提拉","卡米拉",
"艾奇多娜","提丰","赛赫美特","密涅瓦","达芙尼"};//医生姓名
int charge = 200;
int month[13][2]={{0,0},{31,31},{28,29},{31,31},{30,30},{31,31},{30,30},{31,31},{31,31},{30,30},{31,31},{30,30},{31,31}};

typedef struct Doctor{
	char name[10];//名字
	int level;//等级4-1 主任>副主任>主治>住院
	int room;//科室 101-109,201-209
	int code;//10001-10030
	char time[10];//出诊时间
}node2;

typedef struct patient{
	char name[10];//名字
	int age;//年龄
	int ID;//与在链表的位置相关
	int flag[3] = {0}; //检查 开药 住院
	int cost[3] = {0};//记录三种不同的情况花费
    int mi[10] = {0}; //记录每种药开的数量
	int hex = 0;//记录住院押金 ,初始化时请置0
    int InHospitalTime = 0;//天数为单位
    int OutHospitalTime = 0;//20201008
	struct Doctor doctor;
    struct patient * next;
	//struct node2 * next;
}node1;

node1 *head = NULL;//全局头

void Mainmenu(){
	printf("\n");
	printf("           欢迎使用医院诊疗管理系统\n");
	printf("********************************************************\n");
	printf("请输入对应想要查询信息前的行号：\n");
	printf("1.录入诊疗记录\n");
	printf("2.打印科室的诊疗信息\n");
	printf("3.打印医生的诊疗信息\n");
	printf("4.打印患者的所有诊疗信息\n");
	printf("5.修改某条错误的诊疗记录\n");
	printf("6.删除某条诊疗记录\n");
	printf("7.生成目前的住院患者报表\n");
	printf("8.打印指定时间内的诊疗记录\n");
    printf("9.读取\n");
	printf("10.保存\n");
	printf("11.查询某个医生的繁忙程度\n");
	printf("12.离开\n");
	printf("********************************************************\n");
}

/*
functions in total:
node1* InputP();        //1 录入患者信息(测试完毕)
node1* InputD();        //录入医生信息 
void SearchRoom();      //2 打印科室
void PrintRoom();
void SearchDoctor();    //3 打印医生
void PrintDoctor();
void SearchPatient();   //4 打印患者
void PrintPatient();
void Change();          //5 修改
void Delete();          //6 删除
void PrintEx();         //7 生成报表
void PrintTime();       //8 打印指定时间的记录
void Load();            //9 保存
void Save();            //10 读取
void Leave();           //11 退出
node1* change();        //12 修改某条诊疗记录
*/

void Space(){//保持提示信息间的空位
    printf("\n");
    printf("已经返回主菜单,请继续操作\n");
    printf("\n");
}

void mi_cost(node1 *p){   //chy，计算药物价格
	int i , cost = 0;
	for(i = 0 ; i < 10 ; i++){
		if(p->mi[i] > 100 || p->mi[i] < 0) {
			printf("医院共计十种药物：\n");
    	    printf("1:果糖(FOD)\n");
    		printf("2:哌替丁(杜冷丁)\n");
    		printf("3:山莨菪碱(654-2)\n");
    		printf("4:胞磷胆碱钠(COP):\n");
    		printf("5:地西泮(安定)\n");
    		printf("6:呋塞米(速尿)\n");
    		printf("7:间羟胺(阿拉明)\n");
    		printf("8:地塞米松(Dex)\n");
    		printf("9:苯巴比妥(鲁米那钠)\n");
    		printf("10:电脑配件\n\n");
			printf("您在购买ID为%d的药物时输入数量有误,请在这里重新输入想要购买的数量\n",i+1);
			scanf("%d",&p->mi[i]);
			i = 0;
			cost = 0;
			continue;
		}
		if(p->mi[i] <= 100 && p->mi[i] >= 0)
			cost = p->mi[i] * mi_money[i] + cost;
	}
	p->cost[1] = cost;
	return; 
}

void mid(node1 *p){          //chy输入购买药物的数量 
	if(p->flag[1] == 0){
    	for(int i = 0 ; i < 10 ; i++)
    		p->mi[i] = 0;
    	return;
	}
    if(p->flag[1] == 1){           
    	printf("医院共计十种药物：\n");
    	printf("1:果糖(FOD)\n");
    	printf("2:哌替丁(杜冷丁)\n");
    	printf("3:山莨菪碱(654-2)\n");
    	printf("4:胞磷胆碱钠(COP):\n");
    	printf("5:地西泮(安定)\n");
    	printf("6:呋塞米(速尿)\n");
    	printf("7:间羟胺(阿拉明)\n");
    	printf("8:地塞米松(Dex)\n");
    	printf("9:苯巴比妥(鲁米那钠)\n");
    	printf("10:电脑配件\n");
    	printf("请按顺序输入每种药想要购买的数量（0-100）\n\n");
		for(int i = 0 ; i < 10 ; i++){
			scanf("%d",&p->mi[i]);
		}
        mi_cost(p);
        return;
	}                              
} 

bool isLeap(int year){//判断闰年
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int JudgeDay(int t1, int t2){//用于计算住院天数
    int time1,y1,m1,d1;
    int time2,y2,m2,d2;
    time1 = t1;
    time2 = t2;
    if(time1 > time2)
        swap(time1, time2);
    y1 = time1 / 10000, m1 = time1 % 10000 / 100, d1 = time1 % 100;
    y2 = time2 / 10000, m2 = time2 % 10000 / 100, d2 = time2 % 100;
    int ans = 1;
    while(y1 < y2 || m1 < m2 || d1 < d2){
        d1++;
        if(d1 == month[m1][isLeap(y1)] + 1){
            m1 ++;
            d1 = 1;
        }
        if(m1 == 13){
            y1++;
            m1 = 1;
        }
        ans ++;
    }
    return ans;
}
void PrintInHosiptal(node1 *p,int a,int b,int c, int d, int e, int f,int g){//生成具体住院患者信息
       printf("病人名字是：%s\n",p->name);
       printf("患者住院的时间是：%d年%d月%d日%d时%d分\n",a / 1000,a % 1000 / 100,a % 100,b / 100,b % 100);
       printf("患者出院的时间是：%d年%d月%d日%d时%d分\n",c / 1000,c % 1000 / 100,c % 100,d / 100,d % 100);
       printf("患者住院实际天数为：%d天\n",e);
       printf("患者住院收取费用天数为：%d天\n",f);
       printf("收取住院的押金是：%d元\n",g);
       printf("病人住院押金余额是：%d元\n",p->hex);
       return;
}

void InHospital(node1 *p){  //住院 传入具体患者节点
    int Tcharge;  //住院押金所需费用
    int timep1;   //患者住院时间的时和分，格式为0821
    int timep2;   //患者住院时间的年月日,格式为20130101
    int timep3;   //患者出院时间的时和分，格式为0956
    int timep4;   //患者出院的的年月日，格式为20130217
    int hcharge;  //用于存入押金
    printf("病人名字是：%s",p->name);
    printf("请存入住院押金费用\n");
    scanf("%d",&p->hex);
    if(p->hex <= 1000)
    {
        printf("住院押金余额小于1000，请及时充值！\n");
        printf("请存入：\n");
        scanf("%d",&hcharge);
        p->hex = p->hex+hcharge;
        hcharge = 0;
    }
    printf("请录入住院年月日:\n");
    scanf("%d",&timep2);
    if(timep2 <= 20000000 || timep2 >= 30000000)
    {
        do
        {
            printf("输入住院年月日错误，请重新输入\n");
            scanf("%d",&timep2);
            printf("\n");
        }while(timep2 <= 20000000 || timep2 >= 30000000);
    }
    printf("请录入住院间的时分:\n");
    scanf("%d",&timep1);
    printf("\n");
    if(timep1 < 0 || timep2 >= 2400)
    {
        do
        {
            printf("输入住院时分错误，请重新输入\n");
            scanf("%d",&timep1);
            printf("\n");
        }while(timep1 < 0 || timep2 >= 2400);
    }
    printf("请录入出住院年月日:\n");
    scanf("%d",&timep4);
    if(timep4 <= 20000000 || timep4 >= 30000000)
    {
        do
        {
            printf("输入出院年月日错误，请重新输入\n");
            scanf("%d",&timep4);
            printf("\n");
        }while(timep4 <= 20000000 || timep4 >= 30000000);
    }
    printf("请录入住院间的时分:\n");
    scanf("%d",&timep1);
    printf("\n");
    if(timep3 < 0 || timep3 >= 2400)
    {
        do
        {
            printf("输入出院时分错误，请重新输入\n");
            scanf("%d",&timep3);
            printf("\n");
        }while(timep3 <  0 || timep3 >= 2400);
    }
    int N = JudgeDay(timep2,timep4);    //患者住院天数
    p->InHospitalTime = N;
    int M;      //用于计算住院费用
    if(timep1 >= 0 && timep1 <= 800)
    {
        M = N - 1;
    }
    if(timep3 >= 801&&timep3 < 2400)
    {
        Tcharge = charge * M;
        val = val + Tcharge;
    }
    else if(timep3 >= 0 && timep3 <= 800)
    {
        M = M - 1;
        Tcharge = charge * M;
        val = val + Tcharge;
    }
    p->cost[2] = Tcharge;
    printf("住院的押金是:%d\n",Tcharge);
    p->hex = p->hex - Tcharge;
    if(p->hex <= 1000)
    {
        printf("住院押金余额小于1000，请及时充值！\n");
        printf("请存入:");
        scanf("%d",&hcharge);
        p->hex = p->hex + hcharge;
        hcharge = 0;
    }
    printf("住院押金余额是：%d元\n",p->hex);
    val = val + Tcharge;
    PrintInHosiptal(p,timep2,timep1,timep4,timep3,N,M,Tcharge);
    return;
}

void HospitalSet(node1* p){  
    if(p->flag[2]){
        InHospital(p);
    }
    return;
}

node1* InputP(void){   //输入病人各项信息
	node1 *p;
    int x;
    int tem;
    int flag = 0;
    printf("请问您是第一次挂号吗？是则返回1，否则返回0\n");
    scanf("%d",&flag);
	p = (node1*)malloc(sizeof(node1));
    p->next = NULL;
	printf("请输入患者姓名:\n");
	scanf("%s",p -> name);
	printf("请输入患者年龄:\n");
	scanf("%d",&p -> age);
	printf("是否检查，开药，住院？请输入三个数字表示诊疗结果：是则1，否则0。\n");
	for(int i = 0;i < 3;i++)
		p->cost[i] = 0;
	for(int i = 0;i < 3;i++)
		scanf("%d",&p -> flag[i]);
    if(flag){
        p->ID = Pcnt++;
        printf("该患者被分配的ID为:%d\n",p->ID);
    }
    else
    {
        printf("请输入您的ID:\n");
        scanf("%d",&p->ID);
    }
    if(p->flag[1] == 0){
    	for(int i = 0 ; i < 10 ; i++)
    		p->mi[i] = 0;
	}
    if(p->flag[1] == 1){          
			mid(p);
		}
	if(p->flag[2] == 1){          
		printf("请输入住院押金\n");
		scanf("%d",&p->hex);
		printf("请输入住院时间（1-7）\n");                              //新增 
		scanf("%d",&p->InHospitalTime);                                 //新增 
		printf("请输入出院时间（1-7）\n");                              //新增 
		scanf("%d",&p->OutHospitalTime);                                //新增                                    
		p->cost[2] = (p->OutHospitalTime - p->InHospitalTime) * 200;    //新增
		val = val + p->cost[2];
	}
	if(p->flag[2] == 0){                                               //新增 
		p->InHospitalTime = 0;                                         //新增 
		p->OutHospitalTime = 0;                                        //新增 
		p->hex = 0;                                                    //新增 
		}	                              
    //HospitalSet(p);
	printf("注册成功!即将进入医生挂号环节\n\n");
	return p;//返回当前患者节点
}

int JudgeTime(char time[]){  //计算星期
    if(strcmp("mon",time) == 0)
    	return 1;
    if(strcmp("tue",time) == 0)
    	return 2;
    if(strcmp("wed",time) == 0)
    	return 3;
    if(strcmp("tur",time) == 0)
    	return 4;
    if(strcmp("fri",time) == 0)
    	return 5;
    if(strcmp("sat",time) == 0)
        return 6;
    if(strcmp("sun",time) == 0)
    	return 7;
    else
        return 0;
}

void Insert(node1 *p){      //插入新节点
    node1 *p1;
    if(head == NULL){
        head = p;
        p->next = NULL;
    }
    else{
        p1 = head;
        while(p1 && p1->next)
            p1 = p1->next;
        p1->next = p;
        p->next = NULL;
    }
}

void InputD(node1 *p){      //分配医生
    int l1;
    char n1[10];
    printf("请输入想要挂号的医生级别（4 - 1）：\n");
    scanf("%d",&p->doctor.level);
    LOOP:if(p->doctor.level < 1 || p->doctor.level > 4){
        printf("输入错误，请重试！\n");
        printf("请输入想要挂号的医生级别（4 - 1）：\n");
        scanf("%d",&p->doctor.level);
        goto LOOP;
    }
    p->cost[0] = p->doctor.level * 100;           //医生检查费
    val = val + p->cost[0];                       //医院收入
    printf("请输入挂号日期：\n");//输入星期几
    scanf("%s",p->doctor.time);
    if(WeekNum[JudgeTime(p->doctor.time)] == 500){
        printf("当天挂号数已满，请择日再来！\n");
        free(p);
        return;
    }
    else
    {
        WeekNum[JudgeTime(p->doctor.time)]++;
    }
    strcpy(p->doctor.name, DoctorName[(Dcnt - 10000) % 30]);
    p->doctor.code = ((Dcnt++) - 10000) % 30 + 10000;
    p->doctor.room = RoomSelete[(Rcnt++) % 18];
    printf("给您分配的医生信息如下：\n\n");
    printf("姓名为:%s\n",p->doctor.name);
    printf("等级为:%d\n",p->doctor.level);
    printf("工号为:%d\n",p->doctor.code);
    printf("科室为:%d\n",p->doctor.room);
    printf("出诊时间为:%s\n",p->doctor.time);
    Insert(p);
    printf("医生分配成功！\n");
    Space();
}


void SearchRoom(){          //查找科室
	int b;
    printf("请输入想要查询的科室号:\n");
	scanf("%d",&b);//科室号
    LOOP:if(b < 101 || (b > 109 && b < 201) || b > 209){
		    printf("科室输入有误，请重新输入\n");
            printf("请输入想要查询的科室号:\n");
	        scanf("%d",&b);//科室号
		    goto LOOP;
	}
    node1 *p = head;
	while(p){
		if(p->doctor.room == b){
			printf("患者名字为：%s,年龄为：%d\n",p->name,p->age);
			printf("挂号为：%d\n",p->ID);
			if(p->flag[0] == 1)
				printf("该患者进行了检查操作\n");
			if(p->flag[1] == 1)
				printf("该患者进行了开药操作\n");
			if(p->flag[2] == 1)
				printf("该患者进行了住院操作\n");
			printf("为该患者服务的医生为本科室的%s\n",p->doctor.name);
			printf("工号为%d\n",p->doctor.code);
			printf("出诊时间为%s\n",p->doctor.time);
		}
        p = p->next;
	}
    Space();
}

void SearchDoctor(){      //查询医生信息
    int c;
    int flag = 0;
    printf("请输入你想要查询的医生工号:\n");
    scanf("%d",&c);
    LOOP:if(c >= Dcnt || c >= 10030){
            printf("输入有误，请重试\n");
            printf("请输入你想要查询的医生工号:\n");
    		scanf("%d",&c);
            goto LOOP;
    }
    node1 *p = head;
    while(p){
        if(p->doctor.code == c){
            flag = 1;
            printf("该医生信息如下:\n");
            printf("姓名为:%s\n",p->doctor.name);
            printf("等级为:%d\n",p->doctor.level);
            printf("工号为:%d\n",p->doctor.code);
            printf("科室为:%d\n",p->doctor.room);
            printf("出诊时间为:%s\n",p->doctor.time);
        }
        p = p->next;
    }
    if(!flag)
        printf("查找失败，请重试\n");
    Space();
}

void SearchPatient(){     //查询病人信息
    int tem;
    int flag = 0;
    node1* p1 = head;
    printf("请输入病人ID:\n");
    scanf("%d",&tem);
    LOOP:if(tem >= Pcnt){
            printf("此次查找失败，请重试\n");
            printf("请输入病人ID:\n");
    		scanf("%d",&tem);
            goto LOOP;
    }
    while(p1){
        if(p1->ID == tem)
            break;
        p1 = p1->next;
    }
    if(p1){
        flag = 1;
        printf("姓名:%s\n",p1->name);
        printf("年龄：%d\n",p1->age);
        printf("ID:%d\n",p1->ID);
        printf("此次总花费：%d\n",p1->cost[0] + p1->cost[1] + p1->cost[2]);
    }
    if(!flag)
        printf("查找失败，请重试\n");
    Space();
}

void Load(){              //读取
    FILE *fp;
    fp = fopen("inf.txt","r");
    int cnt = 0;
    node1 *p1 = NULL;
    node1 *p2 = NULL;
    while(!feof(fp)){
        cnt++;
        p1 = (node1*)(malloc(sizeof(node1)));
        fscanf(fp,"%s",p1->name);
        fscanf(fp,"%d",&p1->age);
        fscanf(fp,"%d",&p1->ID);
        fscanf(fp,"%d %d %d",&p1->flag[0],&p1->flag[1],&p1->flag[2]);
        fscanf(fp,"%d %d %d",&p1->cost[0],&p1->cost[1],&p1->cost[2]);
		for(int i = 0;i < 10;i++)
            fscanf(fp,"%d",&p1->mi[i]);
        fscanf(fp,"%d",&p1->hex);
        fscanf(fp,"%d",&p1->InHospitalTime);   //新增 
        fscanf(fp,"%d",&p1->OutHospitalTime);  //新增 
        fscanf(fp,"%s",p1->doctor.name);
        fscanf(fp,"%d",&p1->doctor.level);
        fscanf(fp,"%d",&p1->doctor.room);
        fscanf(fp,"%d",&p1->doctor.code);
        fscanf(fp,"%s",p1->doctor.time);
        if(cnt == 1){
            head = p1;
            p2 = p1;
            head->next = NULL;
        }
        else{
            p2->next = p1;
            p2 = p1;
            p2->next = NULL; 
        }
    }
    fclose(fp);
    FILE* fp1;
    fp1 = fopen("inf2.txt","r");
    while(!feof(fp1)){
    fscanf(fp1,"%d",&Dcnt);
    fscanf(fp1,"%d",&Pcnt);
    fscanf(fp1,"%d",&Rcnt);
    fscanf(fp1,"%d",&val);
    for(int i = 1;i <= 7;i++)
        fscanf(fp1,"%d",&WeekNum[i]);
    }
    fclose(fp1);
    printf("读取成功！\n");
    Space();
}

void Save(){       //保存 传入头指针
    FILE *fp;
    fp = fopen("inf.txt","w");
    node1* p1 = head;
    while(p1){
        fprintf(fp,"%s\n",p1->name);
        fprintf(fp,"%d ",p1->age);
        fprintf(fp,"%d\n",p1->ID);
        fprintf(fp,"%d %d %d\n",p1->flag[0],p1->flag[1],p1->flag[2]);
        fprintf(fp,"%d %d %d\n",p1->cost[0],p1->cost[1],p1->cost[2]);
        for(int i = 0;i < 10;i++)
            fprintf(fp,"%d ",p1->mi[i]);
        fprintf(fp,"\n");
        fprintf(fp,"%d\n",p1->hex);
        fprintf(fp,"%d ",p1->InHospitalTime);    //新增 
        fprintf(fp,"%d\n",p1->OutHospitalTime);   //新增 
        fprintf(fp,"%s\n",p1->doctor.name);
        fprintf(fp,"%d ",p1->doctor.level);
        fprintf(fp,"%d ",p1->doctor.room);
        fprintf(fp,"%d\n",p1->doctor.code);
        fprintf(fp,"%s\n",p1->doctor.time);
        p1 = p1->next;        
    }
    fclose(fp);
    FILE* fp1;
    fp1 = fopen("inf2.txt","w");
	fprintf(fp1,"%d\n",Dcnt);
    fprintf(fp1,"%d\n",Pcnt);
    fprintf(fp1,"%d\n",Rcnt);
    fprintf(fp1,"%d\n",val);
    for(int i = 1;i <= 7;i++)
    	fprintf(fp1,"%d ",WeekNum[i]);
    fclose(fp1);
    printf("保存成功！\n");
    Space();
}

void buzy(){   //chy，统计医生出诊情况与繁忙程度
    int i;
	node1* a = head;
    if(a == NULL){
    	printf("当前无储存信息！\n");
    	Space();
    	return;
	}	
	printf("请输入想要得知出诊情况的医生ID(医生ID为10000到10029)\n");
	scanf("%d",&i);
	for(;;){
		if(i >= 10000 && i <= 10029)
            break;
		printf("您的输入有误,请输入为10000到10029的医生ID\n");
		scanf("%d",&i);
	}
	printf("编号为%d的医生，接待病人的名字分别是\n",i);
	while(a){
        if(a->doctor.code == i)
            printf("%s\n",a->name);
        a = a->next;
    }
    Space();
    return;
}

void Change(){                //chy,修改某条诊疗记录,传入头指针
    node1* p1 = head;
	if(p1 == NULL){
    	printf("当前无储存数据！\n");
    	Space();
		return; 
	}
	printf("请输入想要修改的诊疗记录的ID\n");
	int i;
	scanf("%d",&i);       //诊疗记录ID，应为20001-20030
	for( ; ; ){
		if(i > 20000 && i < (Pcnt+1))
			break;
		printf("诊疗记录ID输入有误，请重新输入20001-%d的某个ID\n",Pcnt);
		scanf("%d",&i);
	}
	node1 *q = p1;
	node1 *r = NULL;
	node1 *p = p1;
	//node1 *head = p;
	int x;
	r = (node1*)(malloc(sizeof(node1)));
	while(q != NULL){
		if(q == head && q->ID == i){   //如果要修改的节点是首个节点的情况
			head = r;
			r->next = q->next;
			r->ID = q->ID;
			for( x = 0 ; x < 3 ; x++)
				val = val - q->cost[x];
			free(q);
			printf("请输入患者姓名:\n");
		    scanf("%s",r->name);
		    printf("请输入患者年龄:\n");
			scanf("%d",&r->age);
			printf("是否检查，开药，住院？请输入三个数字表示诊疗结果：是则1，否则0。\n");
			for( x = 0 ; x < 3 ; x++)
				scanf("%d",&r->flag[x]);
			if(r->flag[1] == 1){
				printf("请输入每种药开的数量\n");
				for( x = 0 ; x < 10 ; x++)
				    scanf("%d",&r->mi[x]);
			}
			if(r->flag[1] == 0){
				for( x = 0 ; x < 10 ; x++)
				    r->mi[x] = 0;
			}
			mi_cost(r);
			val = val + r->cost[1];
			if(r->flag[2] == 0){
				r->cost[2] = 0;
				r->hex = 0;
				r->InHospitalTime = 0;
				r->OutHospitalTime = 0;
			}
			if(r->flag[2] == 1){
				printf("请输入住院押金\n");
				scanf("%d",&r->hex);
				printf("请输入住院时间（1-7）\n");                             //新增 
				scanf("%d",&r->InHospitalTime);                                //新增 
				printf("请输入出院时间（1-7），如果暂时不出院请输入0\n");      //新增 
				scanf("%d",&r->OutHospitalTime);                               //新增 
				if(r->OutHospitalTime != 0);                                   //新增
				    r->cost[2] = (r->OutHospitalTime - r->InHospitalTime) * 200;//新增
				if(r->OutHospitalTime == 0){								   //新增 
					printf("请输入当前时间（1-7）\n");                         //新增
					scanf("%d",&x);                                            //新增   
					r->cost[2] = (x - r->InHospitalTime) * 200;                //新增 
				}
			}
			val = val + r->cost[2];
			printf("请输入对应医生编号\n");
        	scanf("%d",&r->doctor.code);
        	printf("请输入该医生等级(1-4)\n");
        	scanf("%d",&r->doctor.level);
			printf("请输入该医生名字\n");
			scanf("%s",r->doctor.name);
			printf("请输入该医生所属科室(101-109,201-209)\n");
			scanf("%d",&r->doctor.room);
			printf("请输入该医生出诊日期\n");
			scanf("%s",r->doctor.time);
			r->cost[0] = r->doctor.level * 100;
			val = val + r->cost[0];
			printf("修改成功!\n");
			Save();
			return; 
		}
		if(q != head && q->ID == i){    //寻找要修改的节点的前置节点
			while(p!=NULL){
				if(p->next == q)
					break;
				p = p->next;
			}
			r->next = q->next;
			r->ID = q->ID;
			p->next = r;
			for(x = 0 ; x < 3 ; x++)
				val = val - q->cost[x];
			free(q);
			printf("请输入患者姓名:\n");
		    scanf("%s",r->name);
		    printf("请输入患者年龄:\n");
			scanf("%d",&r->age);
			printf("是否检查，开药，住院？请输入三个数字表示诊疗结果：是则1，否则0。\n");
			for( x = 0 ; x < 3 ; x++)
				scanf("%d",&r->flag[x]);
			if(r->flag[1] == 0){
				for( x = 0 ; x < 10 ; x++)
				    r->mi[x] = 0;
			}	
			if(r->flag[1] == 1){
				printf("请输入每种药开的数量\n");
				for( x = 0 ; x < 10 ; x++)
				    scanf("%d",&r->mi[x]);
			}
			mi_cost(r); 
			val = val + r->cost[1];
			if(r->flag[2] == 0){
				r->cost[2] = 0;
				r->hex = 0;
				r->InHospitalTime = 0;
				r->OutHospitalTime = 0;
			}
			if(r->flag[2] == 1){
				if(r->flag[2] == 1){
					printf("请输入住院押金\n");
					scanf("%d",&r->hex);
					printf("请输入住院时间（1-7）\n");                             //新增 
					scanf("%d",&r->InHospitalTime);                                //新增 
					printf("请输入出院时间（1-7），如果暂时不出院请输入0\n");      //新增 
					scanf("%d",&r->OutHospitalTime);                               //新增 
					if(r->OutHospitalTime != 0);                                   //新增
				   		r->cost[2] = (r->OutHospitalTime-r->InHospitalTime) * 200;  //新增
					if(r->OutHospitalTime == 0){								   //新增 
						printf("请输入当前时间（1-7）\n");                         //新增
					scanf("%d",&x);                                            	   //新增   
					r->cost[2] = (x - r->InHospitalTime) * 200;                      //新增 
				    }
				}
			}
			val = val + r->cost[2];			
			printf("请输入对应医生编号\n");
        	scanf("%d",&r->doctor.code);
        	printf("请输入该医生等级(1-4)\n");
        	scanf("%d",&r->doctor.level);
			printf("请输入该医生名字\n");
			scanf("%s",r->doctor.name);
			printf("请输入该医生所属科室(101-109,201-209)\n");
			scanf("%d",&r->doctor.room);
			printf("请输入该医生出诊日期\n");
			scanf("%s",r->doctor.time);
			r->cost[0] = r->doctor.level * 100;
			val = val + r->cost[0];
			printf("修改成功!\n");
			Save();
			return; 
		}
		q = q->next;
	}
}

void ResearchTime(node1 *p1){      //chy,生成指定时间段的报表,传入头指针 
	int a,b;
	if(p1 == NULL){
		printf("当前无保存数据！\n");
		return; 
	}
	printf("请输入想要生成报表的日期范围(1-7表示周一到周日)\n");
	scanf("%d%d",&a,&b);
	for(;;){
		if(a < 1 || a > 7 || b < 1 || b > 7){
			printf("日期范围输入错误，请输入1-7表示周一到周日\n");
	    	scanf("%d%d",&a,&b);
		}
		else break;
	}
	node1 *p = p1;
	for(int c = a ; c < (b+1) ; c++){
		printf("周%d\n",c);
		while(p != NULL){
			if(JudgeTime(p->doctor.time) == c){
				printf("患者名字为:%s\n",p->name);
				printf("患者年龄为:%d\n",p->age);
				printf("患者ID为:%d\n",p->ID);
				printf("负责该患者的医生\n名字为:%s\n",p->doctor.name);
				printf("ID为:%d\n",p->doctor.code);
				printf("科室为:%d\n",p->doctor.room);
				if(p->doctor.level == 1)
					printf("等级为住院医师\n");
				if(p->doctor.level == 2)
					printf("等级为主治医师\n");
				if(p->doctor.level == 3)
					printf("等级为副主任\n");
				if(p->doctor.level == 4)
				printf("等级为主任\n");
				printf("该患者进行了：\n");
				if(p->flag[0] == 1)
					printf("检查\n");
				if(p->flag[1] == 1){
					printf("购买了：\n");
					if(p->mi[0] != 0 )
						printf("1:果糖(FOD)%d盒\n",p->mi[0]);
					if(p->mi[1] != 0 )
    					printf("2:哌替丁(杜冷丁)%d盒\n",p->mi[1]);
    				if(p->mi[2] != 0 )
    					printf("3:山莨菪碱(654-2)%d盒\n",p->mi[2]);
    				if(p->mi[3] != 0 )
    					printf("4:胞磷胆碱钠(COP)%d盒\n",p->mi[3]);
    				if(p->mi[4] != 0 )
   	 					printf("5:地西泮(安定)%d盒\n",p->mi[4]);
   	 				if(p->mi[5] != 0 )
    					printf("6:呋塞米(速尿)%d盒\n",p->mi[5]);
    				if(p->mi[6] != 0 )
    					printf("7:间羟胺(阿拉明)%d盒\n",p->mi[6]);
    				if(p->mi[7] != 0 )
    					printf("8:地塞米松(Dex)%d盒\n",p->mi[7]);
    				if(p->mi[8] != 0 )
    					printf("9:苯巴比妥(鲁米那钠)%d盒\n",p->mi[8]);
    				if(p->mi[9] != 0 )
    					printf("10:电脑配件%d盒\n",p->mi[9]);
				}
				if(p->flag[1] == 1)
					printf("住院\n");	
				printf("****************************\n");
			}
			p = p->next;
		}
		p = p1;
	}
    Space();
    return;
}

void ResearchInHospital(node1 *p1){ //生成当前住院患者的报表,传入头指针 
	int a;
	if(p1 == NULL){
		printf("当前无保存数据！\n");
		return; 
	}
	printf("请输入今天的日期(1-7表示周一到周日)\n");
	scanf("%d",&a);
	for(;;){
		if(a < 1 || a > 7){
			printf("日期范围输入错误，请输入1-7表示周一到周日\n");
	    	scanf("%d",&a);
		}
		else break;
	}
	node1 *p = p1;
	while(p != NULL){			
		if(p->flag[2] == 1 && p->InHospitalTime <= a && p->OutHospitalTime > a){
			printf("当前住院的患者名字为：\n");
			printf("%s\n",p->name);
			printf("年龄是%d岁\n",p->age);
			printf("住院押金为：%d元\n",p->hex);
			printf("****************************\n");
		}
		p = p->next;
		if(p == NULL)
		    printf("当前住院患者已经全部输出完毕\n");
	}
    Space();
    return;
}

void Delete(){            //传入头结点
    node1* p1 = head;
	if(p1 == NULL){
    	printf("当前无储存数据！\n");
    	Space();
		return; 
	} 
	printf("请输入想要删除的诊疗记录的ID\n");
	int i;
	scanf("%d",&i);       //诊疗记录ID，应为20001-20030
	for( ; ; ){
		if(i > 20000 && i < Pcnt)
			break;
		printf("诊疗记录ID输入有误，请重新输入\n");
		scanf("%d",&i);
	}        
	int x;
	node1 *p = p1;
	while(p != NULL){
		if(p->ID == i)
			break;
		p = p->next;
	}
	if(p == head){   //如果要删除的节点是首个节点的情况
		head = p->next;
		free(p);
		printf("删除成功!\n");
		Space() ;
		return;
		}
	if(p != head){
		node1 *r = p;
		p = head;
		while(p != NULL){ //寻找前置节点 
			if(p->next == r)
				break;
			p = p->next;
		}
		p->next = r->next;
		free(r);
		printf("删除成功!\n");
        Space();
        return;
	}		
}
void AllDelete(){//删除所有已经存储的节点
    node1* p = head;
    node1* p1 = NULL;
    if(head->next)
        p1 = head->next;
    while(p1){
        delete(p);
        p = p1;
        p1 = p1->next;
    }
    if(p)
        delete(p);
    if(head)
        delete(head);
    printf("内存释放成功！\n");
}
void Exit(){
    int t;
    printf("确定要退出吗？是则1，否则0\n");
    scanf("%d",&t);
    if(t){
        AllDelete();
        exit(0);
    }
    else
        return;
}

/*
functions in total:
node1* InputP();//1 录入患者信息
node1* InputD();
void SearchRoom();//2 打印科室
void PrintRoom();
void SearchDoctor();//3 打印医生
void PrintDoctor();
void SearchPatient();//4 打印患者
void PrintPatient();
void Change();//5 修改
void Delete();//6 删除
void PrintEx();//7 生成报表
void PrintTime();//8 打印指定时间的记录
void Load();//9 读取
void Save();//10 保存
void Leave();//11 退出
node1* change();//12 修改某条诊疗记录
*/

void Choose(){
    int t;
	while(scanf("%d",&t) != EOF){
        node1 *tem = NULL;
        switch(t){
            case 1:tem = InputP();InputD(tem);break;//增加一条诊疗记录
            case 2:SearchRoom();break;  //打印某科室的诊疗记录
            case 3:SearchDoctor();break;//打印某医生的诊疗记录
            case 4:SearchPatient();break;//打印某患者的诊疗记录
            case 5:Change();break;
            case 6:Delete();break;
            case 7:ResearchInHospital(head);break;
            case 8:ResearchTime(head);break;
            case 9:Load();break;
            case 10:Save();break;
            case 11:buzy();break;
            case 12:Exit();break;
        }
    }
}

int main(){
	Mainmenu();
	Choose();
    system("pause");
	return 0;
}
/*这里是第一千行 纪念我们的第一个课设*/
/*  Hospital Management System    */
/*  Members:                      */
/*      LZW CHY WQH               */
/*      Finished in 10.09.2020    */
/*  See You Later                 */
