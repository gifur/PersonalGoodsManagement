// PersonalGM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <malloc.h>
#include <windows.h> 
#include <ctype.h>
#include <conio.h>
#define LEN sizeof(struct wp)     //用户信息结构体的长度； 
#define SLEN sizeof(struct mp)     //用户物品结构体的长度； 
#define MAXN 100
struct wp* head;     //物品链表的头指针 
int n = 0;     //物品数量 
int n1 = 0;     //用户数量 
int f = 0;     //调用用户所用的编号 
int h = 0;     //
int fileflag = 0;     // 
int goodsl = 0;     //分类数量 
int mon[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };     //月份的尾数，查看过期物品时使用 
char goodfl[MAXN][45];     //物品分类，增添新物品时使用 

struct mp     //用户结构体 
{
	int  num;     //用户编号 
	char mc[45];     //用户名称     
	char ps[45];     //用户密码 
};

struct wp     //个人物品 
{
	char wumc[45];     //物品名称  
	int  bh, sl;     //物品编号和数量 
	char begtime[45], deadline[45];     //物品输入时间,过期时间；
	char time[45];     //保质期 
	char fl[45];     //物品分类 
	struct wp* next;
};

struct customer     //用户信息和用户物品数组 
{
	int number;
	struct mp mcps;
	struct wp wuping[1000];
}cus[1000];

int csh(FILE* cfp);     //打开用户信息文件，将用户信息包括昵称、密码存储到结构体数组cus[]中，返回用户的数目
void shuxin(char* enter_1);     //将输入的密码用*号表示的函数
void zhuce(FILE* cfp, int n2);     //注册用户 
void geren(char* mchengdz);     //登陆后进入界面时的函数 
int first(FILE* cfp);     //将用户的物品录入链表和数组的函数 
void caidan(FILE* cfp, char* wenjmc2);     //进入菜单的函数 
void wpguanli(FILE* cfp);     //物品管理界面的函数 
void tianjia(FILE* cfp);     //添加物品界面的函数 
int tianjia_only(FILE* cfp, int n1);
void tianjia_wumc(FILE* cfp);
void tianjia_bh(FILE* cfp);
void chakan(FILE* cfp);     //查看物品信息界面的函数 
void chakan_qb(FILE* cfp, int n1);
void chakan_bh(FILE* cfp, int n1);
void chakan_fl(FILE* cfp);
void chakan_wumc(FILE* cfp);
void chakan_time(FILE* cpf);
void chakan_bd(FILE* cfp);
void tiqu(FILE* cfp);     //提取物品的函数 
void tiqu_bh(FILE* cfp);
void tiqu_wumc(FILE* cfp);
void xiugai(FILE* cfp);     //修改物品界面的函数 
void xiugai_qb(FILE* cfp);
void xiugai_mc(FILE* cfp);
void xiugai_bd(FILE* cfp);
void xiugai_fl(FILE* cfp);
void xiugai_time(FILE* cfp);
void xiugai_sl(FILE* cfp);
int shanchu(FILE* cfp);     //删除物品界面的函数 
int shanchu_wumc(FILE* cfp, int n2);
int shanchu_bh(FILE* cfp, int n2);
void user();     //用户中心界面的函数 
void user_pw();     //用户修改密码 
void guanliyuan();     //管理员界面 
void save(char*);     //加密文件的函数 
void yonghuxuzhi();
long com_year(int y1, int y2);     //查看过期物品时用于计算两个时间之间天数的函数，同以下三个函数 
int com_month(int y1, int m1, int y2, int m2);
int com_day(int y1, int m1, int d1, int y2, int m2, int d2);
int spec_year(int year);

int main()
{
	FILE* mf;
	struct mp* p;
	char* enter;
	char sa[] = { "password.dat" };      //存储用户信息的文件名 
	char mc[45], ps[45];
	int i, j = 0, flag = 1, flag1 = 0;
	struct mp client = { 0,"","" };

	printf("\n\n\n\n\n\n"
		"\t\t****     ****             *****       *****\n"
		"\t\t **       **               ***         ***\n"
		"\t\t **       **                 ***     ***\n"
		"\t\t ***********                  ***   ***\n"
		"\t\t ***********                     ****\n"
		"\t\t **       **                     ***\n"
		"\t\t **       **                     ***\n"
		"\t\t****     ****                   *****\n"
		"\n\t    =================================================\n"
		"\t    =================================================\n\n\n\n");
	save(sa);
	Sleep(1000);

	system("cls");
k:
	printf("\n"
		"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
		"\t\t@            欢迎        进入登陆界面           @\n"
		"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"
		"================================================================================\n");
	if ((mf = fopen("password.dat", "rb+")) == NULL)
	{
		mf = fopen("password.dat", "wb+");
	a:
		printf("欢迎管理员使用该系统，请注册：\n\n");
		do
		{
			printf("请【管理员】输入昵称：(注意！昵称一旦确认不可更改！)\n");
			scanf("%s", mc);
			fflush(stdin);
			strcpy(client.mc, mc);
			printf("请输入您的密码：\n");
			shuxin(ps);
			fflush(stdin);
			printf("请重新输入您的密码：\n");
			shuxin(mc);
			fflush(stdin);
			if (strcmp(ps, mc) == 0) break;
			else
			{
				printf("两次密码输入不一致，请重新输入：\n\n");
			}
		} while (1);
		strcpy(client.ps, ps);
		client.num = n1 + 1;
		printf("您的密码是：【 %s 】  请妥善保管！\n\n", client.ps);
		fwrite(&client, SLEN, 1, mf);
		n1 = csh(mf);
		f = client.num;
		cus[f - 1].mcps.num = f;
		strcpy(cus[f - 1].mcps.mc, client.mc);
		strcpy(cus[f - 1].mcps.ps, client.ps);
		system("pause");
		geren(client.mc);
	}

	else

	{
		do
		{
			system("cls");

			printf("\n"
				"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
				"\t\t@            欢迎        进入登陆界面           @\n"
				"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"
				"================================================================================\n");

			printf("请登录：\n\n");
			flag = 1;
			n1 = csh(mf);
			if (n1 == 0) goto a;
			printf("\t\t\t\t\t\t\t  有【%d】位用户在使用\n\n", n1);
			printf("===============================================================================\n");
			printf("请输入您的昵称：\n\n"
				"\t\t=====================================================\n"
				"\t\t☆ ●如果您需要注册，请输入 “zhuce ” 【注册】 ●☆ \n"
				"\t\t☆ ●如果你需要现在退出，请输入“exit”【退出】 ●☆ \n"
				"\t\t=====================================================\n");
			printf("===============================================================================\n");
			scanf("%s", mc); fflush(stdin);
			if (tolower((int)mc[0]) == 'z' && tolower((int)mc[1]) == 'h' && tolower((int)mc[2]) == 'u'
				&& tolower((int)mc[3]) == 'c' && tolower((int)mc[4]) == 'e' && tolower((int)mc[5]) == '\0')
				zhuce(mf, n1);
			else if (tolower((int)mc[0]) == 'e' && tolower((int)mc[1]) == 'x' && tolower((int)mc[2]) == 'i'
				&& tolower((int)mc[3]) == 't' && tolower((int)mc[4]) == '\0')
			{
				fclose(mf);
				save(sa);
				exit(0);
			}

			else
			{
				rewind(mf);
				while (!feof(mf))
				{
					if (j != 0) fseek(mf, j * SLEN, SEEK_SET);
					fread(&client, SLEN, 1, mf);
					if (strcmp(client.mc, mc) == 0) { flag1 = 1;break; }
					j++;
				}
				if (!flag1)
				{
					printf("\n抱歉，不存在该昵称！请重新输入：");
					system("pause");
				}
				else
				{
					while (flag <= 3)
					{
						printf("请输入您的密码：\n");
						shuxin(ps);fflush(stdin);
						if (strcmp(client.ps, ps) == 0)
						{
							printf("登陆成功！\n");
							fclose(mf);
							f = client.num;
							geren(client.mc); 	                                                     //接口…… 
						}
						else
						{
							if (flag != 3) printf("\n提示：昵称或密码错误！你还剩下 %d 次输入机会！\n", 3 - flag);
						}
						flag++;
					}
					printf("\n提示：昵称或密码错误！\n");
					printf("\n您是否需要注册？ 如需注册请输入 【zhuce】 否则按任意键退出\n");
					scanf("%s", mc); fflush(stdin);
					if (tolower((int)mc[0]) == 'z' && tolower((int)mc[1]) == 'h' && tolower((int)mc[2]) == 'u'
						&& tolower((int)mc[3]) == 'c' && tolower((int)mc[4]) == 'e' && tolower((int)mc[5]) == '\0')
						zhuce(mf, n1);
					else return 1;
				}
			}


		} while (1);
	}
}


int csh(FILE* cfp)
{
	int i = 0;
	struct mp client = { 0,"","" };

	rewind(cfp);
	fread(&client, SLEN, 1, cfp);
	while (!feof(cfp))
	{
		cus[i].mcps.num = cus[i].number = client.num;
		strcpy(cus[i].mcps.mc, client.mc);
		strcpy(cus[i].mcps.ps, client.ps);
		fread(&client, SLEN, 1, cfp);
		i++;
	}
	return(i);
}


void shuxin(char* enter_1)
{
	int i = 0, j = 0;
	char c;
	for (;;)
	{
		c = _getch();
		if (j == 0)
		{
			if ((int)c == 13)
			{
				printf("不好意思，您必须输入密码！");
				printf("\n请输入密码：");
			}
			else if ((int)c == 8) *enter_1 = '\0';
			else
			{
				j = 1;
				*enter_1 = c;
				enter_1++;
				i++;
				printf("*");
			}
		}
		else
		{
			if (i >= 29 && (int)c != 13 && (int)c != 8) *enter_1 = '\0';
			else if ((int)c == 8)
			{
				if (i > 0)
				{
					i--;
					enter_1--;
					*enter_1 = '\0';
					printf("\b");
					printf(" ");
					printf("\b");
				}
				else
				{
					j = 0;
					*enter_1 = '\0';
				}
			}
			else if ((int)c == 13) break;
			else
			{
				*enter_1 = c;
				enter_1++;
				i++;
				printf("*");
			}
		}
	}
	*enter_1 = '\0';
	printf("\n");
}




void zhuce(FILE* cfp, int n2)
{

	char* enter;
	char mc[45], ps[45];
	int i = 0;
	int flag = 0;
	struct mp client = { 0,"","" };


	do
	{
		system("cls");
		printf("\n"
			"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n"
			"\t\t@         欢迎注册   使用个人物品管理           @\n"
			"\t\t@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\n"
			"================================================================================\n");
		printf("请输入您的新昵称：（注意昵称一旦输入不可更改）\n");
		scanf("%s", mc);fflush(stdin);
		for (i = 0;i < n1;i++)
		{
			if (strcmp(cus[i].mcps.mc, mc) == 0)
			{
				printf("对不起，该昵称已存在，请重新输入：\n");
				system("pause");
				flag = 1;break;
			}
		}
		if (flag == 1) { flag = 0;continue; }
		strcpy(client.mc, mc);
		printf("请输入您的密码：\n");
		shuxin(ps); fflush(stdin);
		printf("请重新输入您的密码：\n");
		shuxin(mc);  fflush(stdin);
		if (strcmp(ps, mc) == 0) break;
		else
		{
			printf("两次密码输入不一致!请重新输入：\n\n");
			system("pause");
		}
	} while (1);
	strcpy(client.ps, ps);
	client.num = n1 + 1;
	printf("您的密码是：【 %s 】 请妥善保管！\n\n", client.ps);
	fseek(cfp, n2 * SLEN, SEEK_SET);
	fwrite(&client, SLEN, 1, cfp);
	n1 = csh(cfp);
	fileflag = 1;
	printf("已注册用户数量：%d\n", n1);
	system("pause");
	f = client.num;
	geren(client.mc);
	return;
}

//之前的为系统登录等为发生的情况所写的代码，下面是登录成功后的代码即个人物品管理



void geren(char* mchengdz)     //个人世界
{
	FILE* fp;
	char wenjmc[45], houzui[] = { ".dat" };
	int i = 0, j, ok = 0;
	char* baocun = mchengdz;
	while (*mchengdz != '\0')
	{
		wenjmc[i] = *mchengdz;
		i++;
		mchengdz++;
	}
	wenjmc[i] = '\0';
	strcat(wenjmc, houzui);
	if (!fileflag)  save(wenjmc);
	if ((fp = fopen(wenjmc, "rb+")) == NULL)
	{
		fp = fopen(wenjmc, "wb+");
	}
	n = first(fp);
	caidan(fp, baocun);
}

int first(FILE* cfp)   //这里的feof函数还需要更改 
{
	struct wp* p1, * p2;
	int i = 0, j, ok = 0, k = 0;
	struct wp  client = { " ",0,0, " "," "," "," " };
	head = (struct wp*)malloc(LEN);
	rewind(cfp);
	fread(&client, LEN, 1, cfp);
	{
		strcpy(head->wumc, client.wumc);
		strcpy(cus[f - 1].wuping[i].wumc, client.wumc);
		strcpy(head->begtime, client.begtime);
		strcpy(cus[f - 1].wuping[i].begtime, client.begtime);
		strcpy(head->deadline, client.deadline);
		strcpy(cus[f - 1].wuping[i].deadline, client.deadline);
		strcpy(head->time, client.time);
		strcpy(cus[f - 1].wuping[i].time, client.time);
		strcpy(head->fl, client.fl);
		strcpy(cus[f - 1].wuping[i].fl, client.fl);
		cus[f - 1].wuping[i].bh = head->bh = client.bh;
		cus[f - 1].wuping[i].sl = head->sl = client.sl;
		head->next = NULL;
		i++;
	}
	p1 = (struct wp*)malloc(LEN);
	p2 = head->next;
	fread(&client, LEN, 1, cfp);
	while (!feof(cfp))
	{
		strcpy(p1->wumc, client.wumc);
		strcpy(cus[f - 1].wuping[i].wumc, client.wumc);
		strcpy(p1->begtime, client.begtime);
		strcpy(cus[f - 1].wuping[i].begtime, client.begtime);
		strcpy(p1->deadline, client.deadline);
		strcpy(cus[f - 1].wuping[i].deadline, client.deadline);
		strcpy(p1->time, client.time);
		strcpy(cus[f - 1].wuping[i].time, client.time);
		strcpy(p1->fl, client.fl);
		for (j = 0; j < k; j++)
			if (strcmp(goodfl[j], p1->fl) == 0)
			{
				ok = 1; break;
			}
		if (ok == 0 && strcmp(p1->fl, "") != 0) strcpy(goodfl[k++], p1->fl);
		else ok = 0;
		strcpy(cus[f - 1].wuping[i].fl, client.fl);
		cus[f - 1].wuping[i].bh = head->bh = client.bh;
		cus[f - 1].wuping[i].sl = head->sl = client.sl;
		p1->bh = client.bh;
		p1->sl = client.sl;
		p1->next = NULL;
		if (i == 1) head->next = p1;
		else p2->next = p1;
		p2 = p1;
		p1 = (struct wp*)malloc(LEN);
		i++;
		fread(&client, LEN, 1, cfp);
	}
	if (strcmp(head->wumc, " ") == 0) i = 0;
	goodsl = k;
	return(i);
}


void caidan(FILE* cfp, char* wenjmc2)
{
	int enter, flag;
	char wenjim[45], sav[45];
	int i = 0, j;
	char sa[] = { "password.dat" };
	while (*wenjmc2 != '\0')
	{
		sav[i] = wenjim[i] = *wenjmc2;
		i++;wenjmc2++;
	}
	sav[i] = wenjim[i] = '\0';
	strcat(sav, ".dat");
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t     欢迎 【%s】 来到个人物品管理系统         \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n", wenjim);
		printf("                                                             库存更新到：<%d>\n\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】------------------------------个人物品管理*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】------------------------------用户管理中心*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】-----------------------------用户须知/帮助*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】----------------------------------退    出*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n请选择；\n");
		flag = scanf("%d", &enter);                                                 //scanf函数若出错就返回0，以flag获得返回值
		if (flag)                                                                        //判断flag是否为0，防止输入出错
			switch (enter)                                                                   //判断输入的操作数
			{
			case 1:wpguanli(cfp);break;                                                //操作数为1时，进入添加函数
			case 2:user(); break;
			case 3:yonghuxuzhi(); break;                                                         //2时，进入修改函数
			case 4:
				fclose(cfp);
				save(sav);
				save(sa);
				system("cls");
				printf("\n"
					"\t\t                  ***     ***\n"
					"\t\t               ***  *** ***  ***\n"
					"\t\t             ***      ***      ***\n"
					"\t\t           ***      *******     ***\n"
					"\t\t         ***       ***   ***      ***\n"
					"\t\t        ***       ***     ***      ***\n"
					"\t\t         ***       ***   ***      ***\n"
					"\t\t           ***      *******     ***\n"
					"\t\t             ***      ***     ***\n"
					"\t\t               ***  *** ***  ***\n"
					"\t\t                  ***      ***\n"
					"\n\t\t                                      本程序由【雪影蓝枫】编写\n");
				system("pause");
				exit(0);

			default:printf("错误指示！请重新输入：\n");system("pause");                                        //输入不在范围的操作数，提示错误
			}

		else
		{
			getchar();                                                                //若上边输入的不是数字，此函数会过滤所输入的字符，并提示输入有误
			printf("错误指示！请重新输入：\n");
			system("pause");
		}
	} while (1);

}


void wpguanli(FILE* cfp)
{
	int enter, flag;
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||        欢迎来到个人物品管理中心             ||\n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】----------------------------------添加物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】----------------------------------查看物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】----------------------------------提取物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】----------------------------------修改物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【5】----------------------------------删除物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【6】-----------------------------------返   回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n请选择：\n");
		flag = scanf("%d", &enter);                                                 //scanf函数若出错就返回0，以flag获得返回值
		if (flag)
			switch (enter)                                                                 //判断输入的操作数
			{
			case 1:tianjia(cfp);break;                                               //操作数为1时，进入添加函数
			case 2:chakan(cfp);break;
			case 3:tiqu(cfp);break;
			case 4:xiugai(cfp);break;                                                          //2时，进入修改函数
			case 5:shanchu(cfp);break;
			case 6:return;
			default:printf("错误！请重新输入：\n\n");system("pause");                                        //输入不在范围的操作数，提示错误
			}
		else
		{
			getchar();                                                                //若上边输入的不是数字，此函数会过滤所输入的字符，并提示输入有误
			printf("错误！请重新输入：\n\n");
			system("pause");
		}
	} while (1);

}



void tianjia(FILE* cfp)
{
	int enter, flag;
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||               物品添加菜单                  || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】--------------------------------添加新物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】------------------------按已存物品名称添加*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】------------------------按已存物品编号添加*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】-----------------------------------返   回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n 请输入您的选择：\n");
		flag = scanf("%d", &enter);
		if (flag)
			switch (enter)
			{
			case 1:n = tianjia_only(cfp, n);break;
			case 2: tianjia_wumc(cfp);break;
			case 3: tianjia_bh(cfp); break;
			case 4: return;
			default: printf("错误指令，请重新输入！\n");
			}

		else
		{
			getchar();
			printf("错误指令，请重新输入！\n");
		}
	} while (1);

}


int tianjia_only(FILE* cfp, int n2)    //直接添加物品 
{
	struct wp* p1, * p2;
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, n1 = n2 + 1, k, j;
	i = 0;
	p1 = p2 = (struct wp*)malloc(LEN);
	p2 = head;

	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                添加新物品                   || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                              库存更新到：<%d>\n", n);
	printf("输入添加物品的名称：\n");
	scanf(" %s", p1->wumc);
	getchar();
	while (p2 != NULL)
	{
		if (strcmp(p2->wumc, p1->wumc) == 0)
		{
			printf("该物品名称已存在，请先查看！\n");
			system("pause");
			return(n2);
		}
		p2 = p2->next;
	}
	p2 = head;
	p1->bh = n2 + 1;
	printf("添加的物品所在位置的编号是；%d", p1->bh);
	printf("\n输入添加物品的数量：（提示：仅输入数字）\n");
	scanf("%d", &p1->sl);
	getchar();
	printf("输入添加物品的时间（生产时间）：（格式：0000-00-00）\n");
	scanf("%s", p1->begtime);//fflush(stdin);
	getchar();
	printf("输入物品的过期时间：（格式：日期：0000-00-00）\n");
	scanf("%s", p1->deadline);
	getchar();
	printf("输入物品的保质期：\n");
	scanf("%s", p1->time);
	getchar();
	printf("现存物品分类有如下：\n");
	printf("\n*******************************************************************************\n");
	for (k = 0; k < goodsl; k++)
	{
		printf("%3d) ", k + 1);
		printf("%10s", goodfl[k]);
		if ((1 + k) % 4 == 0) printf("\n");
	}
	printf("\n*******************************************************************************\n");
	printf("\n按编号输入物品的类型：\n");
	printf("没有自己需要的分类?需要添加新的分类请输入最后一位编号再加1\n");
v:
	scanf("%d", &j);
	getchar();
	fflush(stdin);
	if (k + 1 < j) { printf("输入错误，请重新输入：\n"); goto v; }
	else if (k >= j)
	{
		k = 1;
		while (k++ != j);
		strcpy(p1->fl, goodfl[k - 2]);
		puts(p1->fl);
	}
	else if (k + 1 == j)
	{
		printf("请输入新的分类名\n");
		scanf("%s", p1->fl);
		strcpy(goodfl[j - 1], p1->fl);
		goodsl++;
	}
	p1->next = NULL;
	if (i != 1) fseek(cfp, n2 * LEN, SEEK_SET);
	fwrite(p1, LEN, 1, cfp);
	if (n2 == 0) { head = p1;head->next = NULL; }
	else
	{
		for (i = 1;i < n1 - 1;i++) p2 = p2->next;
		p2->next = p1;
	}
	cus[f - 1].wuping[p1->bh - 1].bh = p1->bh;
	strcpy(cus[f - 1].wuping[p1->bh - 1].wumc, p1->wumc);
	strcpy(cus[f - 1].wuping[p1->bh - 1].fl, p1->fl);
	strcpy(cus[f - 1].wuping[p1->bh - 1].begtime, p1->begtime);
	strcpy(cus[f - 1].wuping[p1->bh - 1].deadline, p1->deadline);
	cus[f - 1].wuping[p1->bh - 1].sl = p1->sl;
	printf("物品添加成功！");
	system("pause");
	return(n1);

}


void tianjia_wumc(FILE* cfp)   //添加物品 
{
	struct wp* p1, * p2;
	struct wp  client = { "", 0, 0, "", "","","" };
	int i = 0;
	char ch[45];
	p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品名称添加                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("请输入所需添加的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				{
					printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
					printf("================================================================================\n");
				}
				if (p1->sl != 0)
				{
					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
				}
				printf("================================================================================\n");
				printf("\n请输入添加该物品的数量：\n");
				scanf("%d", &i);
				getchar();
				p1->sl += i;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				client.sl += i;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				cus[f - 1].wuping[p1->bh - 1].sl += i;
				printf("成功添加物品！目前 %s 的数量为：%d ", p1->wumc, p1->sl);
				system("pause");
				return;
			}
			p1 = p1->next;
		} while (p1 != NULL);
		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}
}


void tianjia_bh(FILE* cfp)    //添加物品 
{
	struct wp* p1, * p2;
	struct wp  client = { "", 0, 0, "", "","","" };     //
	int i, t;
	p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品编号添加                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n\n", n);
	printf("请输入所需添加的物品的编号：\n");
	scanf("%d", &t);
	getchar();
	if (head != NULL)
		do
		{
			if (p1->bh == t) break;
			p1 = p1->next;
		} while (p1 != NULL);
		if (p1 == NULL)
		{
			printf("未找到该物品的编号，请查询是否存在！\n");
			system("pause");
		}
		else
		{
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
			}
			if (p1->sl != 0) {
				printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
					p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
			}
			printf("\n请输入添加该物品的数量：\n");
			scanf("%d", &i);
			getchar();
			p1->sl += i;
			fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
			fread(&client, LEN, 1, cfp);
			client.sl += i;
			fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
			fwrite(&client, LEN, 1, cfp);
			printf("物品添加成功，%s 的数量为<%d>\n", p1->wumc, p1->sl);
			system("pause");
			cus[f - 1].wuping[p1->bh - 1].sl += i;
			return;
		}
}


void chakan(FILE* cfp)
{
	int enter, flag;
	struct wp* p1, * p2;
	p1 = p2 = (struct wp*)malloc(LEN);
	int i, j;
	char ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||                查看物品                     || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】----------------------------------查看全部*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】----------------------------------分类一览*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】--------------------------------按编号查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】--------------------------------按名称查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【5】--------------------------------按分类查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【6】----------------------------已删除物品查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【7】--------------------------物品保质状况查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【8】-----------------------按录入\\录出时间查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【9】----------------------------------模糊查询*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【0】----------------------------------返    回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");

		printf("\n请输入您的选择：\n");
		flag = scanf("%d", &enter);
		if (flag)
			switch (enter)
			{
			case 1: chakan_qb(cfp, n);break;
			case 3: chakan_bh(cfp, n);break;
			case 4: chakan_wumc(cfp);break;
			case 5: chakan_fl(cfp);break;
			case 8: chakan_bd(cfp);break;
			case 7: chakan_time(cfp);break;
			case 6: {
				rewind(cfp);
				fread(&client, LEN, 1, cfp);
				int y = 0;
				while (!feof(cfp))
				{

					if (client.bh == 1)printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
					if (client.sl == 0)
					{
						printf("||%8s  || %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
							client.wumc, client.bh, client.sl, client.begtime, client.deadline, client.time, client.fl);
						y++;
					}
					fread(&client, LEN, 1, cfp);

				}
				if (y != 0)
				{
					printf("==================================================\n"
						"\n共有删除物品数目为：%d\n", y);
				}


				else printf("\n暂无已删除的物品，你删除试试？\n");
				system("pause");}
				  break;
			case 2:
				p1 = p2 = head;
				system("cls");
				printf(
					"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
					"\t\t||             查看分类物品                    || \n"
					"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
				printf("================================================================================\n");
				printf("||  物品类型  ||\t||该分类物品种类的数量||\n");
				for (i = 0; i < goodsl; i++)
				{
					j = 0;
					while (p1 != NULL)
					{
						if (strcmp(goodfl[i], p1->fl) == 0) j++;
						p1 = p1->next;
					}
					printf("||%10s  ||\t||%10d         ||\n", goodfl[i], j);
					p1 = head;
				}
				printf("===============================================================================\n");
				system("pause");
				break;
			case 9:
			{
				system("cls");
				printf(
					"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
					"\t\t||               模糊查找                      || \n"
					"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
				printf("================================================================================\n");
				printf("输入你模糊出现的字符：");
				scanf("%s", ch);
				getchar();
				int y = 0;
				printf("===============================================================================\n"
					"|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				rewind(cfp);
				fread(&client, LEN, 1, cfp);
				while (!feof(cfp))
				{

					if (strstr(client.wumc, ch) != NULL || strstr(client.begtime, ch) != NULL || strstr(client.deadline, ch) != NULL || strstr(client.fl, ch) != NULL)
					{
						printf("||%8s  || %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
							client.wumc, client.bh, client.sl, client.begtime, client.deadline, client.time, client.fl);
						y++;
					}
					fread(&client, LEN, 1, cfp);
				}
				if (y != 0)
				{
					printf("===============================================================================\n"
						"\n共有物品数目为：%d\n", y);
					system("pause");
				}
				else
				{
					printf("你的记忆真的很模糊，模糊查找都没用！！\n");
					system("pause");
				}
			}

			case 0: return;
			default: printf("错误指令，请重新输入！\n");
			}

		else
		{
			getchar();
			printf("错误指令，请重新输入！\n");
		}

	} while (1);

}


void chakan_qb(FILE* cfp, int n1)
{
	struct wp  client = { "Nothing", 0, 0, "null", "null","null""null" };
	int i = 0, flag = 1;
	char enter;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             查看全部物品                    || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("\n全部物品列表：\n\n");
	rewind(cfp);
	fread(&client, LEN, 1, cfp);
	while (!feof(cfp))
	{
		if (i == 0) printf("===============================================================================\n"
			"|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
		if (client.sl != 0)
			printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n", client.wumc, client.bh, client.sl, client.begtime, client.deadline, client.time, client.fl);
		fread(&client, LEN, 1, cfp);
		i++;
		if ((flag++) == 20)
		{
			printf("===============================================================================\n");
			flag = 0;
			printf("是否翻页？是的话请输入R，否则输入其他键:\n");
			getchar();
			scanf("%c", &enter);
			getchar();
			if (enter == 'r' || enter == 'R')
			{
				system("cls");
				printf("===============================================================================\n"
					"|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");

			}
			else { system("pause"); return; }
		}
	}
	printf("===============================================================================\n");
	system("pause");
	return;
}


void chakan_bh(FILE* cfp, int n1)
{
	struct wp* p1, * p2;
	int i, bh, flag = 0;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品编号查询                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("请输入物品的编号：\n");
	scanf("%d", &bh);
	if (bh > n1)
	{
		printf("您输入的编号不存在！\n");system("pause"); return;
	}
	p1 = p2 = head;
	for (i = 1;i < bh;i++) p1 = p1->next;
	{
		{
			printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
			printf("================================================================================\n");
		}
		if (p1->sl != 0) {
			printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
				p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl); flag = 1;
		}
		printf("================================================================================\n");
		if (!flag) printf("你查找的物品已删除！\n");
	}
	system("pause");
	return;
}


void chakan_fl(FILE* cfp)
{

	struct wp* p1, * p2;
	int i, flag = 0, flag1 = 1;
	char ch[45];
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||             按物品分类查看                  || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("================================================================================\n");
		printf("                                                               库存更新到：<%d>\n", n);
		printf("请输入物品的类别：\n");
		scanf("%s", ch);
		getchar();
		p1 = p2 = head;
		while (p1 != NULL)
		{
			if (p1 == head)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
			}
			if (strcmp(p1->fl, ch) == 0)
			{
				flag++;
				{
					if (p1->sl != 0) {
						printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
							p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					}
				}
			}
			p1 = p1->next;
		}
		printf("================================================================================\n");
		printf("属于【%s】分类的物品共有<%d>种\n\n", ch, flag);
		if (!flag)
		{
			printf("您输入的类别不存在！\n");
			system("pause");
			break;
		}
		else
		{
			system("pause"); return;
		}
	} while (1);

}


void chakan_wumc(FILE* cfp)
{
	struct wp* p1, * p2;
	int i;
	char ch[45];
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品名称查看                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("请输入您要查看的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	p1 = p2 = head;
	while (p1 != NULL)
	{
		if (strcmp(p1->wumc, ch) == 0)
		{
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
			}
			if (p1->sl != 0)
			{
				printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
					p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
			}
			printf("===============================================================================\n");
			system("pause");
			return;
		}
		p1 = p1->next;
	}
	if (p1 == NULL)
	{
		printf("您所要查看的物品不存在！\n");system("pause");return;
	}
}


void chakan_time(FILE* cfp)
{
	char s[45], s1[5], s2[7], s3[9], s4[5], s5[7], s6[9], guoqi[] = "已过期";
	int c1, c2, c3, c4, c5, c6;
	int n1, m, i, flag = 0, enter;
	unsigned  sum = 0;
	struct wp* p1, * p2;
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||              物品状况查看                   || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("================================================================================\n");
		printf("                                                               库存更新到：<%d>\n", n);
		printf("输入要查找的时间:（输入的为今天的日期）1900~3000 格式：1987-02-09\n");
		scanf("%s", s);
		fflush(stdin);
		memcpy(s1, s, 4);
		for (i = 5;i < 7;i++)  s2[i - 5] = s[i];
		for (i = 8;i < 10;i++) s3[i - 8] = s[i];
		s1[4] = '\0';
		s2[2] = '\0';
		s3[2] = '\0';
		c1 = atoi(s1);
		c2 = atoi(s2);
		c3 = atoi(s3);
	} while (c3 > mon[c2 - 1] || c2 >= 13 || c1 < 1900 || c1>3000);

	do
	{
	V:
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||              物品状况查看                   || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("================================================================================\n");
		printf("                                                             库存更新到：<%d>\n\n", n);
		printf("您输入的时间为： %d年%d月%d日 \n\n", c1, c2, c3);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】----------------------90天内过期的物品查看*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】----------------------物品保质剩余天数查看*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】--------------------------------已过期物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】----------------------------------返    回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("输入您要查询的项目：");
		flag = scanf("%d", &enter);
		if (flag)
		{
			if (enter == 1 || enter == 2 || enter == 3 || enter == 4) break;
			else printf("输入有误！请重新输入");
		}
		else printf("输入有误！请重新输入");

	} while (1);

	p1 = p2 = head;
	while (p1 != NULL)
	{
		memcpy(s4, p1->deadline, 4);
		for (i = 5;i < 7;i++)  s5[i - 5] = p1->deadline[i];
		for (i = 8;i < 10;i++)  s6[i - 8] = p1->deadline[i];
		s4[4] = '\0';
		s5[2] = '\0';
		s6[2] = '\0';
		c4 = atoi(s4);
		c5 = atoi(s5);
		c6 = atoi(s6);
		if (enter == 1)
		{
			if (p1 == head)
			{
				printf("90天内过期的物品清单：\n\n");
				printf("|| 物品名称 ||物品编号|||离过期的天数|| 物品分类 ||\n");
				printf("================================================================================\n");
			}
			if (c4 < c1 || (c4 >= c1 && c5 < c2) || (c4 >= c1 && c5 >= c2 && c6 < c3)) p1 = p1;
			else
			{
				sum += com_year(c1, c4);                                /*计算两个年份之间的天数*/
				sum += com_month(c1, c2, c4, c5);                 /*计算两个月份之间的天数*/
				sum += com_day(c1, c2, c3, c4, c5, c6);
				if (sum <= 90)
				{
					if (p1->sl != 0) printf("||%10s|| %3d  ||   %8u ||%10s||\n", p1->wumc, p1->bh, sum, p1->fl);
				}
			}
		}

		if (enter == 2)
		{
			if (p1 == head)
			{
				printf("全部物品保质天数查看：\n\n");
				printf("|| 物品名称 ||物品编号|||离过期的天数|| 物品分类 ||\n");
				printf("================================================================================\n");
			}
			if (c4 < c1 || (c4 == c1 && c5 < c2) || (c4 == c1 && c5 == c2 && c6 < c3) && p1->sl != 0)
			{
				printf("||%10s|| %3d  || %10s ||%10s||\n", p1->wumc, p1->bh, guoqi, p1->fl);
			}
			else
			{
				sum += com_year(c1, c4);                                /*计算两个年份之间的天数*/
				sum += com_month(c1, c2, c4, c5);                 /*计算两个月份之间的天数*/
				sum += com_day(c1, c2, c3, c4, c5, c6);
				if (p1->sl != 0) printf("||%10s|| %3d  || %10u ||%10s||\n", p1->wumc, p1->bh, sum, p1->fl);
			}

		}

		if (enter == 3)
		{
			if (p1 == head)
			{
				printf("已过期的物品清单：\n\n");
				printf("||物品名称||物品编号||物品分类||  性质 ||\n");
				printf("================================================================================\n");
			}
			if (c4 < c1 || (c4 == c1 && c5 < c2) || (c4 == c1 && c5 == c2 && c6 < c3) && p1->sl != 0)
				printf("||%8s|| %3d  ||%10s|| %s ||\n", p1->wumc, p1->bh, p1->fl, guoqi);

		}

		if (enter == 4) return;
		p1 = p1->next;
		sum = 0;
	}
	printf("================================================================================\n");
	if (!flag)
	{
		printf("不存在相应的物品\n");
		system("pause");
		return;
	}
	else
	{
		system("pause"); goto V;
	}
	return;

}


void chakan_bd(FILE* cfp)
{
	char s[45], s1[5], s2[7], s3[9], s4[5], s5[7], s6[9];
	int c1, c2, c3, c4, c5, c6;
	int x, y, z, n1, m, w, i, flag = 0;
	struct wp* p1, * p2;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品时间查看                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("输入要查找的时间:（格式：0000-00-00）为防止查找失败请按照格式输入\n");
	scanf("%s", s);
	memcpy(s1, s, 4);
	for (i = 5;i < 7;i++) s2[i - 5] = s[i];
	for (i = 7;i < 9;i++) s3[i - 7] = s[i];
	s1[4] = '\0';
	s2[6] = '\0';
	s3[8] = '\0';
	c1 = atoi(s1);
	c2 = atoi(s2);
	c3 = atoi(s3);
	p1 = p2 = head;

	while (p1 != NULL)
	{
		memcpy(s4, p1->begtime, 4);
		for (i = 5;i < 7;i++) s5[i - 5] = p1->begtime[i];
		for (i = 7;i < 9;i++) s6[i - 7] = p1->begtime[i];
		s4[4] = '\0';
		s5[6] = '\0';
		s6[8] = '\0';
		c4 = atoi(s4);
		c5 = atoi(s5);
		c6 = atoi(s6);

		if (p1 == head)
		{
			printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
			printf("================================================================================\n");
		}
		if (strcmp(p1->begtime, s) == 0 || strcmp(p1->deadline, s) == 0)
		{
			flag++;
			if (p1->sl != 0)
				printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
					p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
		}
		p1 = p1->next;
	}
	printf("================================================================================\n");
	printf("在{%s}时间录入或录出的物品共有<%d>种\n\n", s, flag);
	if (!flag)
	{
		printf("您输入的类别不存在！\n");
		system("pause");
		return;
	}
	else
	{
		system("pause");
		return;
	}
	return;
}


void tiqu(FILE* cfp)
{
	int enter, flag;
	system("cls");
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||               提取物品                      || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】--------------------------------按名称提取*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】----------------------------按已存编号提取*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】----------------------------------返    回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n请输入您的选择：\n");
		flag = scanf("%d", &enter);
		if (flag)
			switch (enter)
			{
			case 1: tiqu_wumc(cfp);break;
			case 2: tiqu_bh(cfp);break;
			case 3: return;
			default: printf("错误指令，请重新输入！\n！");
			}
		else
		{
			getchar();
			printf("错误指令，请重新输入！\n！");
		}
	} while (1);

}


void tiqu_bh(FILE* cfp)
{
	struct wp* p1, * p2;
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, j, bh;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||           按编号提取物品                    || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("===============================================================================\n");
	printf("请输入你要提取的物品的编号：\n");
	scanf("%d", &bh);
	getchar();
	if (bh > n || bh <= 0)
	{
		printf("不存在此编号，请查询！");
		system("pause");
		return;
	}
	p1 = p2 = head;
	for (i = 1;i < bh;i++)
	{
		if (i != 1) p2 = p2->next;
		p1 = p1->next;
	}
	printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
	printf("================================================================================\n");
	if (p1->sl != 0)printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
		p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
	else
	{
		printf("该物品已删除，请在查看菜单查看已删除物品！\n");
		return;
	}
	printf("该物品剩余件数为：<%d>\n", p1->sl);
	printf("请输入你需要提取的件数： ");
	scanf("%d", &j);
	getchar();
	p1->sl -= j;
	printf("剩余物品数量：%d\n", p1->sl);
	if (p1->sl == 0)
	{
		printf("该物品库存数量为零，请及时添加！否则将清空该位置\n");
		if (p1->next != NULL)
		{
			if (p1 == head) head = p1->next;
			else p1->next = p2->next;
		}
		else
		{
			if (p1 == head)
			{
				printf("无物品储存状态……\n");
				system("pause");
			}
			else p2->next = NULL;
		}

	}
	if (i != 1) fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
	fread(&client, LEN, 1, cfp);
	client.sl -= j;
	fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
	fwrite(&client, LEN, 1, cfp);
	cus[f - 1].wuping[p1->bh - 1].sl -= j;
	printf("物品提取成功！"); system("pause");return;
}


void xiugai(FILE* cfp)
{

	int enter, flag;
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||               物品修改菜单                  || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】------------------------修改物品的全部内容*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】------------------------------修改物品名称*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】--------------------修改物品生产和过期时间*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】------------------------  修改物品的保质期*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【5】----------------------------修改物品的分类*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【6】-----------------------------------返   回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n 请输入您的选择：\n");


		flag = scanf("%d", &enter);
		if (flag)
			switch (enter)
			{
			case 1: xiugai_qb(cfp);break;
			case 2: xiugai_mc(cfp);break;
			case 3: xiugai_bd(cfp); break;
			case 4: xiugai_time(cfp); break;
			case 5: xiugai_fl(cfp); break;
			case 6: return;
			default: printf("错误指令，请重新输入！\n");
			}
		else
		{
			getchar();
			printf("错误指令，请重新输入！\n");
		}
	} while (1);

}


void xiugai_fl(FILE* cfp)
{
	struct wp* p1, * p2, * q1, * p3;
	p3 = (struct wp*)malloc(LEN);
	char ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, k, j, n2 = n1;
	p3 = q1 = p2 = p1 = (struct wp*)malloc(LEN);
	q1 = p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                修改物品的分类               || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("请输入所需修改的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
				if (p1->sl != 0)
				{

					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					printf("===============================================================================\n");
				}
				else
				{
					printf("该物品已删除，请在查看菜单查看已删除物品！\n");
					return;
				}
				printf("现存物品分类有如下：\n");
				printf("\n*******************************************************************************\n");
				for (k = 0; k < goodsl; k++)
				{
					printf("%3d) ", k + 1);  printf("%10s", goodfl[k]);
					if ((1 + k) % 4 == 0) printf("\n");
				}
				printf("\n*******************************************************************************\n");
				printf("\n按编号输入修改后物品的类型：\n");
				printf("没有自己需要的分类?需要添加新的分类请输入最后一位编号再加1\n");
			v:
				scanf("%d", &j);
				getchar();
				fflush(stdin);
				if (k + 1 < j) { printf("输入错误，请重新输入：\n"); goto v; }
				else if (k >= j)
				{
					k = 1;
					while (k++ != j) strcpy(p3->fl, goodfl[k - 1]);
				}
				else if (k + 1 == j)
				{
					printf("请输入新的分类名\n");
					scanf("%s", p1->fl);
					fflush(stdin);
					strcpy(goodfl[j - 1], p1->fl);
					goodsl++;
				}
				puts(p1->fl);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.fl, p1->fl);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				strcpy(cus[f - 1].wuping[p1->bh - 1].wumc, p1->wumc);
				printf("物品修改成功！");
				system("pause");
				return;
			}
			q1 = p1;
			p1 = p1->next;
		} while (p1 != NULL);

		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}
}


void xiugai_time(FILE* cfp)
{
	struct wp* p1, * p2, * q1, * p3;
	p3 = (struct wp*)malloc(LEN);
	char	ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, k, j, n2 = n1;
	p3 = q1 = p2 = p1 = (struct wp*)malloc(LEN);
	q1 = p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                修改物品保质期               || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");

	printf("请输入所需修改的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
				if (p1->sl != 0)
				{
					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					printf("===============================================================================\n");
				}
				else
				{
					printf("该物品已删除，请在查看菜单查看已删除物品！\n");
					return;
				}

				printf("\n输入修改后物品的保质期：\n");
				scanf("%s", p1->time);
				getchar();
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.time, p1->time);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				strcpy(cus[f - 1].wuping[p1->bh - 1].time, p1->time);
				printf("物品修改成功！");
				system("pause");
				return;
			}
			q1 = p1;
			p1 = p1->next;

		} while (p1 != NULL);

		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}
}


void xiugai_bd(FILE* cfp)
{
	struct wp* p1, * p2, * q1, * p3;
	p3 = (struct wp*)malloc(LEN);
	char	ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, k, j, n2 = n1;
	p3 = q1 = p2 = p1 = (struct wp*)malloc(LEN);
	q1 = p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                修改物品时间                 || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");

	printf("请输入所需修改的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
				if (p1->sl != 0) {
					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					printf("===============================================================================\n");
				}
				else
				{
					printf("该物品已删除，请在查看菜单查看已删除物品！\n");
					return;
				}
				printf("\n输入修改后物品的时间（生产时间）：（格式：0000-00-00）\n");
				scanf("%s", p1->begtime);//fflush(stdin);
				getchar();
				printf("\n输入修改后物品的过期时间：（格式：日期：0000-00-00）\n");
				scanf("%s", p1->deadline);
				getchar();
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.begtime, p1->begtime);
				strcpy(client.deadline, p1->deadline);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				strcpy(cus[f - 1].wuping[p1->bh - 1].begtime, p1->begtime);
				strcpy(cus[f - 1].wuping[p1->bh - 1].deadline, p1->deadline);
				printf("物品修改成功！");
				system("pause");
				return;
			}
			q1 = p1;
			p1 = p1->next;

		} while (p1 != NULL);

		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}
}


void xiugai_qb(FILE* cfp)
{

	struct wp* p1, * p2, * q1, * p3;
	p3 = (struct wp*)malloc(LEN);
	char ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, k, j, n2 = n1;
	p3 = q1 = p2 = p1 = (struct wp*)malloc(LEN);
	q1 = p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                修改物品全部内容             || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");

	printf("请输入所需修改的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
				if (p1->sl != 0)
				{
					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					printf("================================================================================\n");
				}
				else
				{
					printf("该物品已删除，请在查看菜单查看已删除物品！\n");
					return;
				}

				printf("输入修改后的名称：\n");
				scanf(" %s", p3->wumc);
				getchar();
				while (p2 != NULL)
				{
					if (strcmp(p2->wumc, p3->wumc) == 0)
					{
						printf("该物品名称已存在，请先查看！\n");
						system("pause");
						return;
					}
					p2 = p2->next;
				}
				printf("\n输入添加物品的数量：（提示：仅输入数字）\n");
				scanf("%d", &p3->sl);
				getchar();
				p3->bh = p1->bh;
				printf("\n输入修改后物品的时间（生产时间）：（格式：0000-00-00）\n");
				scanf("%s", p3->begtime);//fflush(stdin);
				getchar();
				printf("\n输入修改后物品的过期时间：（格式：日期：0000-00-00）\n");
				scanf("%s", p3->deadline);
				getchar();
				printf("\n输入修改后物品的保质期：\n");
				scanf("%s", p3->time);
				getchar();
				printf("现存物品分类有如下：\n");
				printf("\n*******************************************************************************\n");
				for (k = 0; k < goodsl; k++)
				{
					printf("%3d) ", k + 1);printf("%10s", goodfl[k]); if ((1 + k) % 4 == 0) printf("\n");
				}
				printf("\n*******************************************************************************\n");
				printf("\n按编号输入修改后物品的类型：\n");
				printf("没有自己需要的分类?需要添加新的分类请输入最后一位编号再加1\n");
			v:
				scanf("%d", &j);
				getchar();
				fflush(stdin);
				if (k + 1 < j) { printf("输入错误，请重新输入：\n"); goto v; }
				else if (k >= j)
				{
					k = 1;
					while (k++ != j) strcpy(p3->fl, goodfl[k - 1]);
				}
				else if (k + 1 == j)
				{
					printf("请输入新的分类名\n");
					scanf("%s", p3->fl);
					fflush(stdin);
					strcpy(goodfl[j - 1], p3->fl);
					goodsl++;
				}
				puts(p3->fl);
				p3->next = p1->next;
				q1->next = p3;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.wumc, p3->wumc);
				strcpy(client.begtime, p3->begtime);
				strcpy(client.deadline, p3->deadline);
				strcpy(client.time, p3->time);
				strcpy(client.fl, p3->fl);
				client.sl = p3->sl;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				cus[f - 1].wuping[p1->bh - 1].bh = p1->bh;
				strcpy(cus[f - 1].wuping[p1->bh - 1].wumc, p3->wumc);
				strcpy(cus[f - 1].wuping[p1->bh - 1].fl, p3->fl);
				strcpy(cus[f - 1].wuping[p1->bh - 1].begtime, p3->begtime);
				strcpy(cus[f - 1].wuping[p1->bh - 1].time, p3->time);
				strcpy(cus[f - 1].wuping[p1->bh - 1].deadline, p3->deadline);
				cus[f - 1].wuping[p1->bh - 1].sl = p1->sl;
				printf("物品修改成功！");
				system("pause");
				return;
			}
			q1 = p1;
			p1 = p1->next;
		} while (p1 != NULL);

		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}

}


void tiqu_wumc(FILE* cfp)
{
	struct wp* p1, * p2;
	struct wp  client = { "", 0, 0, "", "","" };
	int i = 0, flag, enter;
	char ch[45];
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||           按名称提取物品                    || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("===============================================================================\n");
	printf("请输入提取物品的名称：\n");
	scanf("%s", ch);
	getchar();
	p1 = p2 = head;
	while (p1 != NULL)
	{
		if (i != 1) p2 = p2->next;
		if (strcmp(p1->wumc, ch) == 0)
		{
			printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
			printf("================================================================================\n");
			if (p1->sl != 0)printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
				p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
			printf("================================================================================\n");
			printf("剩余该物品的件数：<%d>\n", p1->sl);
			do
			{
				printf("输入需要提取的数量：\n");
				flag = scanf("%d", &enter);
				if (flag == 1 && (enter >= 0 && enter <= p1->sl))
				{
					p1->sl -= enter;
					printf("剩下物品数量：<%d>\n", p1->sl);
					if ((p1->bh - 1) != 0) fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
					fread(&client, LEN, 1, cfp);
					client.sl -= enter;
					fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
					fwrite(&client, LEN, 1, cfp);
					cus[f - 1].wuping[p1->bh - 1].sl = client.sl;
					break;
				}
				else
				{
					getchar();
					printf("错误指令！\n");
					system("pause");
					return;
				}
			} while (1);
			if (p1->sl == 0)
			{
				printf("该物品库存为零，系统清空该物品存储空间\n");
				if (p1->next != NULL)
				{
					if (p1 == head) head = p1->next;
					else p1->next = p2->next;
				}
				else
				{
					if (p1 == head) head = NULL;
					else p2->next = NULL;
				}
			}
			system("pause");
			return;
		}
		p1 = p1->next;
		i++;
	}
	if (p1 == NULL)
	{
		printf("您所要查看的物品不存在！\n");system("pause");return;
	}
}


void xiugai_mc(FILE* cfp)
{
	struct wp* p1, * p2, * q1, * p3;
	p3 = (struct wp*)malloc(LEN);
	char ch[45];
	struct wp  client = { "", 0, 0, "", "","","" };
	int i, k, j, n2 = n1;
	p3 = q1 = p2 = p1 = (struct wp*)malloc(LEN);
	q1 = p1 = p2 = head;
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||                修改物品名称                 || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");

	printf("请输入所需修改的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	if (head != NULL)
		do
		{
			if (strcmp(p1->wumc, ch) == 0)
			{
				printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
				printf("================================================================================\n");
				if (p1->sl != 0) {
					printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
						p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
					printf("================================================================================\n");
				}
				else
				{
					printf("该物品已删除，请在查看菜单查看已删除物品！\n");
					return;
				}
				printf("输入修改后的名称：\n");
				scanf(" %s", ch);
				getchar();
				while (p2 != NULL)
				{
					if (strcmp(p2->wumc, ch) == 0)
					{
						printf("该物品名称已存在，请先查看！\n");
						system("pause");
						return;
					}
					p2 = p2->next;
				}
				strcpy(p1->wumc, ch);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.wumc, p1->wumc);
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				strcpy(cus[f - 1].wuping[p1->bh - 1].wumc, p1->wumc);
				printf("物品修改成功！");
				system("pause");
				return;
			}
			q1 = p1;
			p1 = p1->next;
		} while (p1 != NULL);

		if (p1 == NULL)
		{
			printf("未找到该物品，请查询是否存在！\n");
			system("pause");
		}
}


int shanchu(FILE* cfp)           //删除物品 
{
	int enter, flag;
	int i, j;
	char houzui[] = { ".dat" }, daiti[45];
	FILE* D;
	do
	{
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||               物品删除菜单                  || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】----------------------------按物品名称删除*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】----------------------------按物品编号删除*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】------------------------------删除全部物品*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】-----------------------------------返   回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");
		printf("\n 请输入您的选择：\n");


		flag = scanf("%d", &enter);getchar();
		if (flag)
			switch (enter)
			{
			case 1:n = shanchu_wumc(cfp, n);shanchu(cfp);
			case 2:n = shanchu_bh(cfp, n);break;
			case 3: {
				printf("确定要删除全部？继续请按Y，否则请按任意键！\n");
				char insert;
				scanf("%c", &insert);
				if (insert == 'y' || insert == 'Y')
				{
					strcpy(daiti, cus[f - 1].mcps.mc);
					strcat(daiti, houzui);
					D = fopen(daiti, "w+");
					head = NULL;
					printf("物品已清空，残留痕迹可能重新启动才能清理\n");
					n = 0;

				}
				system("pause");} break;
			case 4: return 1;
			default: printf("错误指令，请重新输入！\n");
			}
		else
		{
			getchar();
			printf("错误指令，请重新输入！\n");
		}
	} while (1);

}


int shanchu_wumc(FILE* cfp, int n2)
{
	struct wp* p1, * p2;
	int i = n2;
	char ch[45], enter;
	struct wp  client = { "", 0, 0, "", "","","" };
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品名称删除                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("请输入您要删除的物品的名称：\n");
	scanf("%s", ch);
	getchar();
	p1 = p2 = head;
	while (p1 != NULL)
	{
		if (strcmp(p1->wumc, ch) == 0)
		{
			printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
			printf("================================================================================\n");
			printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n\n\n",
				p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
			printf("确定删除该物品！输入Y或N继续：\n");
			scanf("%c", &enter);
			if (tolower(enter) == 'y')
			{
				if (p1->next != NULL)
				{
					if (p1 == head) head = p1->next;
					else p1->next = p2->next;
				}
				else
				{
					if (p1 == head) head = NULL;
					else p2->next = NULL;
				}
				if (p1->bh != 1)fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.fl, "null");
				strcpy(client.begtime, "null");
				strcpy(client.deadline, "null");
				strcpy(client.time, "null");
				client.sl = 0;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				cus[f - 1].wuping[p1->bh - 1].sl = 0;
				printf("删除成功！\n"); system("pause");return(--i);
			}
			else
			{
				printf("回到个人物品管理中心！\n"); return(i);
			}
		}
		p1 = p1->next;
	}
	if (p1 == NULL)
	{
		printf("您所要删除的物品不存在！\n");system("pause");return(i);
	}
}


int shanchu_bh(FILE* cfp, int n2)
{

	struct wp* p1, * p2;
	int i = n2;
	int bh;
	char ch[45], enter, cin;
	struct wp  client = { "", 0, 0, "", "","" };
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||             按物品编号删除                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("================================================================================\n");
	printf("                                                               库存更新到：<%d>\n", n);
	printf("请输入您要删除的物品的编号：\n");
	scanf("%d", &bh);
	getchar();
	p1 = p2 = head;
	while (p1 != NULL)
	{
		if (p1->bh == bh)
		{
			printf("|| 物品名称  || 编号 ||  数量  || 存入时间 || 最后期限 || 保质期 || 物品类别 ||\n");
			printf("================================================================================\n");
			printf("|| %10s|| %3d  ||%8d||%10s||%10s||%5s   ||%10s||\n",
				p1->wumc, p1->bh, p1->sl, p1->begtime, p1->deadline, p1->time, p1->fl);
			printf("================================================================================\n\n");
			printf("确定删除该物品！输入Y或N继续：\n");
			scanf("%c", &enter);
			if (tolower(enter) == 'y')
			{
				if (p1->next != NULL)
				{
					if (p1 == head) head = p1->next;
					else p1->next = p2->next;
				}
				else
				{
					if (p1 == head) head = NULL;
					else p2->next = NULL;
				}
				rewind(cfp);
				if (p1->bh != 1)fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fread(&client, LEN, 1, cfp);
				strcpy(client.time, "null");
				strcpy(client.fl, "null");
				strcpy(client.begtime, "null");
				strcpy(client.deadline, "null");
				client.sl = 0;
				fseek(cfp, (p1->bh - 1) * LEN, SEEK_SET);
				fwrite(&client, LEN, 1, cfp);
				cus[f - 1].wuping[p1->bh - 1].sl = 0;
				printf("删除成功！\n"); system("pause");return(--i);
			}
			else
			{
				printf("回到个人物品管理中心！\n"); return(i);
			}
		}
		p1 = p1->next;

	}
	if (p1 == NULL)
	{
		printf("您所要删除的物品不存在！\n");system("pause");return(i);
	}
}


void user()
{
	int flag, enter;
	char cin;
	FILE* fk = fopen("yonghufankui.dat", "a+");

	do {
		system("cls");
		printf(
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
			"\t\t||           欢迎来到用户管理中心              || \n"
			"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
		printf("                                                             库存更新到：<%d>\n\n", n);
		printf("===============================================================================\n");
		printf("||\t\t***************************************************          ||\n");
		printf("||\t\t\\*【1】----------------------------------修改密码*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【2】-----------------------------AAA管理员权限*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【3】----------------------------------用户反馈*\\          ||\n");
		printf("||\t\t===================================================          ||\n");
		printf("||\t\t\\*【4】----------------------------------返    回*\\          ||\n");
		printf("||\t\t***************************************************          ||\n");
		printf("===============================================================================\n");

		printf("\n请输入您的选择：\n");
		flag = scanf("%d", &enter);
		if (flag)
			switch (enter)
			{
			case 1: user_pw();system("pause");break;
			case 2:guanliyuan();break;
			case 3:printf("设立缘由：\n"
				"您用了个人物品管理之后，肯定有些感想吧？\n"
				"向管理员说出你的心声，反馈你宝贵的意见以让管理员进行升级该系统，相信在你的帮助下\n"
				"个人物品管理系统会越来越完善\n");
				printf("\n请吐槽：提示：输入完毕后请输入 # 号退出\n");
				cin = getchar();
				cin = 10;
				while (cin != '#')
				{
					fputc(cin, fk);
					cin = getchar();
				}
				fclose(fk);
				putchar(10);
				printf("输入成功，谢谢你的反馈！\n");
				system("pause");
				break;

			case 4:return;
			default: printf("错误指令，请重新输入！\n"); system("pause");
			}
		else
		{
			getchar();
			printf("错误指令，请重新输入！\n");
		}
	} while (1);
}


void user_pw()     //修改用户密码 
{
	FILE* cpf = fopen("password.dat", "rb+");
	rewind(cpf);
	char password1[45], mingcheng[45];
	int i = 1, j = 1, flag = 0;
	struct mp client = { 0,"","" };
	system("cls");
	printf(
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
		"\t\t||               修改用户密码                  || \n"
		"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
	printf("\n为保护您和他人的隐私，请先输入您的昵称： \n");
	scanf("%s", mingcheng);
	getchar();
	printf("\n请输入旧密码:\n");
	shuxin(password1); fflush(stdin);
	fread(&client, SLEN, 1, cpf);
	while (!feof(cpf))
	{
		if (strcmp(client.ps, password1) == 0 && strcmp(client.mc, mingcheng) == 0)
		{
			flag = 1;
			break;
		}
		else { fread(&client, SLEN, 1, cpf);i++; }
	}
	if (!flag)
	{
		printf("昵称或密码错误！取消本次操作！");
		system("pause");
		return;
	}
	do
	{
		printf("请输入新密码：\n");
		shuxin(client.ps);fflush(stdin);
		printf("请再次输入新密码：\n");
		shuxin(password1);fflush(stdin);
		if (strcmp(client.ps, password1) == 0)
		{
			fseek(cpf, (i - 1) * SLEN, SEEK_SET);
			fwrite(&client, SLEN, 1, cpf);
			fclose(cpf);
			strcpy(cus[i - 1].mcps.ps, client.ps);
			printf("昵称：%s 密码：%s\n", client.mc, client.ps);
			printf("修改成功！请妥善保管您的密码！\n");
			return;
		}
		else
		{
			printf("两次输入的密码不相同，请重新输入！\n\n");
			if (j != 5)
			{
				printf("\n密码输入错误！\n");
				printf("您还可以再输入 <%d> 次！\n", (5 - j));
				j++;
				system("pause");
			}
			else
			{
				printf("超过输入次数，返回修改菜单！\n\n");
				system("pause");
				return;
			}

		}

	} while (1);
}


void guanliyuan()
{
	int i, j, flag, enter;
	FILE* select = fopen("password.dat", "r+");
	FILE* qinkong;
	struct mp  client = { 0,"","" }, Delete = { 0,"","" };
	char ps[45], houzui[] = { ".dat" }, ch;
	system("cls");
	do
	{
		printf(
			"\t\t     &                   &&\n"
			"\t\t   &&&&                &&   &\n"
			"\t\t&&&&&&&&&&&&&&&&&&&&&&&    &&&\n"
			"\t\t                      &&    &\n"
			"\t\t                         &&\n"
			"\t\t\n"
			"\t\t=================================\n"
			"\t\t=================================\n\n");
		printf("===============================================================================\n\n");

		printf("此权限属于管理员，请输入管理员密码：\n");
		shuxin(ps);fflush(stdin);
		if (strcmp(cus[0].mcps.ps, ps) == 0)
		{
		b:
			system("cls");
			printf(
				"\t\t     &                   &&\n"
				"\t\t   &&&&                &&   &\n"
				"\t\t&&&&&&&&&&&&&&&&&&&&&&&    &&&\n"
				"\t\t                      &&    &\n"
				"\t\t                         &&\n"
				"\t\t\n"
				"\t\t=================================\n"
				"\t\t=================================\n\n");
			printf("===============================================================================\n\n");
			printf(
				"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n"
				"\t\t||                管理员权限                   || \n"
				"\t\t+++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
			printf("===============================================================================\n\n");
			printf("*****************************************\n");
			printf("*共有【 %d 】位用户在使用个人物品管理系统*\n", n1);
			printf("*****************************************\n\n");



			printf("===============================================================================\n");
			printf("||\t\t***************************************************          ||\n");
			printf("||\t\t\\*【1】----------------------------------查看用户*\\          ||\n");
			printf("||\t\t===================================================          ||\n");
			printf("||\t\t\\*【2】------------------------------清除所有用户*\\          ||\n");
			printf("||\t\t===================================================          ||\n");
			printf("||\t\t\\*【3】------------------------------初始化该系统*\\          ||\n");
			printf("||\t\t===================================================          ||\n");
			printf("||\t\t\\*【4】------------------------------查看用户反馈*\\          ||\n");
			printf("||\t\t===================================================          ||\n");
			printf("||\t\t\\*【5】----------------------------------返    回*\\          ||\n");
			printf("||\t\t***************************************************          ||\n");
			printf("===============================================================================\n");



			printf("\n请输入您的选择：\n");
			flag = scanf("%d", &enter);
			getchar();
			if (flag)
				switch (enter)
				{
				case 1: {
					printf("\t\t            || 用户编号 || 用户昵称 ||\n");
					printf("\t\t================================================\n");
					for (i = 0;i < n1;i++)
					{
						printf("\t\t             { %5d     ||%8s  } \n", cus[i].mcps.num, cus[i].mcps.mc);
					}
					printf("\t\t================================================\n");
					system("pause");
				};goto b;
				case 2: {
					printf("确定要删除所有的用户？如果想继续请输入Y，否则请按任意（除Y）键\n");
					char insert;
					scanf("%c", &insert);
					if (insert == 'y' || insert == 'Y')
					{
						rewind(select);
						fread(&client, SLEN, 1, select);
						printf("%d,%s,%s\n", client.num, client.mc, client.ps);
						fread(&Delete, SLEN, 1, select);
						while (!feof(select))
						{
							strcat(Delete.mc, houzui);
							qinkong = fopen(Delete.mc, "w+");
							fclose(qinkong);
							fread(&Delete, SLEN, 1, select);
						}
						fclose(select);
						select = fopen("password.dat", "w+");
						rewind(select);
						fwrite(&client, SLEN, 1, select);
						fclose(select);
						printf("已删除其他所有的用户!\n");
						system("pause");
					}
				};goto b;
				case 3: {
					printf("确定要删除所有的用户？如果想继续请输入Y，否则请按任意（除Y）键\n");
					char insert;
					scanf("%c", &insert);
					if (insert == 'y' || insert == 'Y')
					{
						rewind(select);
						fread(&client, SLEN, 1, select);
						printf("%d,%s,%s", client.num, client.mc, client.ps);
						fread(&Delete, SLEN, 1, select);
						while (!feof(select))
						{
							strcat(Delete.mc, houzui);
							qinkong = fopen(Delete.mc, "w+");
							fclose(qinkong);
							fread(&Delete, SLEN, 1, select);
						}
						fclose(select);
						select = fopen("password.dat", "w+");
						system("del \"password.dat\"");
						fclose(select);
						printf("已删除所有的用户（包括管理员）!\n");
					}
				};exit(0);
				case 4:
					printf("===============================================================================\n");
					qinkong = fopen("yonghufankui.dat", "r+");
					while ((ch = fgetc(qinkong)) != EOF)
						putchar(ch);
					printf("\n");
					printf("===============================================================================\n");
					fclose(qinkong);
					fclose(select);
					printf("是否要清空用户反馈？需要的话请输入【Y】否则按任意键继续……\n");
					scanf("%c", &ch);
					if (tolower((int)ch) == 'y') qinkong = fopen("yonghufankui.dat", "w+");
					else goto b;
					printf("用户反馈已经清空！");
					system("pause");
					system("cls");
					goto b;
				case 5:    return;
				default:   printf("错误指令，请重新输入！\n");
				}
			else
			{
				getchar();
				printf("错误指令，请重新输入！\n");
			}
		}
		else
		{
			printf("密码错误！\n");
			system("pause");
			return;
		}
	} while (1);
}


void save(char* filename)
{
	char password[] = "password";
	const char* filenametemp = "temp12345678901234567890.temp";
	FILE* fp;
	FILE* fptemp;
	char ch = 0;
	int i = 0;
	if ((fp = fopen(filename, "rb")) == NULL)
	{
		return;
	}
	fptemp = fopen(filenametemp, "wb");
	while (1)
	{
		ch = fgetc(fp);
		if (feof(fp))   break;
		ch ^= password[i++];
		fputc(ch, fptemp);
		if (i == 5)     i = 0;
	}
	fclose(fp);
	fclose(fptemp);
	remove(filename);
	rename(filenametemp, filename);
}


void yonghuxuzhi()
{
	FILE* fp = fopen("yonghuxuzhi.dat", "r");
	char ch;
	while ((ch = fgetc(fp)) != EOF)
		putchar(ch);
	fclose(fp);
	system("pause");
	return;
}

long com_year(int y1, int y2)                                      /*计算两个年份之间的天数*/
{
	int i;
	long sum = 0;
	for (i = y1 + 1;i < y2;i++)
	{
		if (spec_year(i))
			sum += 366;
		else
			sum += 365;
	}
	return sum;
}


int com_month(int y1, int m1, int y2, int m2)                       /*计算两个月份之间的天数*/
{
	int i;
	int sum = 0;
	if (y1 != y2)
	{
		if (spec_year(y1)) mon[1] = 29;
		if (m1 != m2)
		{
			for (i = m1;i < 12;i++) sum += mon[i];
			mon[1] = 28;
			if (spec_year(y2))   mon[1] = 29;
			for (i = 0;i < m2 - 1;i++)  sum += mon[i];
			mon[1] = 28;
		}
		else
		{
			for (i = m1 - 1;i < 12;i++)   sum += mon[i];
			mon[1] = 28;
			if (spec_year(y2))   mon[1] = 29;
			for (i = 0;i < m2 - 1;i++)   sum += mon[i];
			mon[1] = 28;
		}
	}
	else
	{
		if (spec_year(y1))   mon[1] = 29;
		for (i = m1;i < m2 - 1;i++)   sum += mon[i];
		mon[1] = 28;
	}
	return sum;
}


int com_day(int y1, int m1, int d1, int y2, int m2, int d2)             /*计算两天之间的天数*/
{
	int i;
	int sum = 0;
	if (m1 != m2)
	{
		if (spec_year(y1))   mon[1] = 29;
		sum += (mon[m1 - 1] - d1);
		sum += d2;
		mon[1] = 28;
	}
	else  sum += d2 - d1;
	return sum;
}


int spec_year(int year)                                           /*判断是否为闰年*/
{
	if ((year % 400 == 0) || ((year % 4 == 0) && (year % 100 != 0)))
		return 1;
	else
		return 0;
}




