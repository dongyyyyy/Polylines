#include "OpenCV.h"
#include "ArrayList.h"


pointList* lists;

int main()
{
	Mat image;
	int wait = 10;
	int c;
	lists = (pointList*)calloc(1, sizeof(pointList));
	initList(lists);
	image = imread("./Image/person_259.jpg", CV_LOAD_IMAGE_COLOR);

	resizeWindow("Original", 100, 100);
	imshow("Original", image);
	
	setMouseCallback("Original", onMouse, (void*)(&image));

	c = waitKey(0);
	if (c == 'a')
	{
		setMouseCallback("Original", onMouseCheck, (void*)(&image));
		waitKey(0);
	}
	else if (c == 27)
	{
		return 0;
	}
	destroyAllWindows();
	return 0;
}
void onMouseCheck(int event, int x, int y, int flags, void* param)
{
	Mat* im = reinterpret_cast<Mat*>(param);
	int i = 0;
	int size;
	switch (event)
	{
	case CV_EVENT_LBUTTONDOWN:
		checkIn(im,x,y);
		break;
	}
}
void onMouse(int event, int x, int y, int flags, void* param)
{
	Mat* im = reinterpret_cast<Mat*>(param);
	int i = 0;
	int size;
	switch(event)
	{
		case CV_EVENT_LBUTTONDOWN:
			ListAdd(lists, x, y);
			draw_line(im);
			break;
		case CV_EVENT_RBUTTONDOWN:
			ListRemove(lists, x, y);
			draw_line(im);
			break;
	} 
}

void initList(pointList* l) // ����Ʈ �ʱ�ȭ
{
	l->size = 0;
	l->front = NULL;
	l->back = NULL;
}

void ListAdd(pointList* l, int x, int y)// ����Ʈ �߰�
{
	pointNode* news = (pointNode*)calloc(1, sizeof(pointNode));
	news->x = x;
	news->y = y;
	news->next = NULL;
	news->prev = l->back;
	if (l->front == NULL) // empty
	{
		l->front = news;
		l->back = news;
	}
	else
	{
		//printf("news.x = %d , news.y = %d\n", news->x, news->y);
		l->back->next = news;
		l->back = news;
	}
	l->size++;
}
int ListRemove(pointList* l, int x, int y) // ����Ʈ ����
{
	if (l->front == NULL && l->back == NULL)
	{
		printf("Can't remove\n");
		return -1;
	}
	else if (l->front == l->back)
	{
		l->front = NULL;
		l->back = NULL;
		l->size--;
		return 0;
	}
	else
	{
		pointNode* cur = l->front;
		while (cur != NULL)
		{
			if ((cur->x <= (x + 10) && cur->x >= (x - 10)) && (cur->y <= (y + 10) && cur->y >= (y - 10)))
			{
				if(cur->next !=NULL)
				{
					cur->next->prev = cur->prev;
					cur->prev->next = cur->next;
				}
				if (cur->next == NULL)
				{
					cur->prev->next = NULL;
					l->back = cur->prev;
				} 
				cur->prev = NULL;
				cur->next = NULL;
				l->size--;

			}
			cur = cur->next;
		}
		//free(cur);
		return 1;
	}
}
void ListPrint(pointList* l)
{
	pointNode* cur = l->front;
	if (cur == NULL)
	{
		printf("List is Empty\n");
		return;
	}
	while (cur != NULL)
	{
		printf("X : %d,Y : %d\n", cur->x, cur->y);
		cur = cur->next;
	}
	puts("");
	free(cur);
}

void ListToArray1(pointList* l, Point* ary)
{
	int i = 0;
	pointNode* cur = l->front;
	if (cur == NULL)
	{
		printf("List is Empty\n");
		return;
	}
	while (cur != NULL)
	{
		ary[i++] = Point(cur->x, cur->y);
		cur = cur->next;
	}
	puts("");
	free(cur);
}

void ListToArray2(pointList* l , Point **ary)
{
	int i = 0;
	pointNode* cur = l->front;
	if (cur == NULL)
	{
		printf("List is Empty\n");
		return;
	}
	while (cur != NULL)
	{
		ary[0][i++] = Point(cur->x, cur->y);
		cur = cur->next;
	}
	puts("");
	free(cur);
}

void draw_line(Mat *im)
{
	//Point** points;
	Point* points;
	int i = 0;
	int size = 0;
	//points = (Point * *)calloc(2, sizeof(pointList*));
	//for (i = 0; i < 2; i++)
	//{
	points = (Point*)calloc(lists->size, sizeof(Point));
	//}
	size = lists->size;
	ListToArray1(lists, points);
	for (i = 0; i < size; i++)
	{
		printf("points->x : %d , points->y : %d\n", points[i].x, points[i].y);
	}
	//const Point* ppt[1] = { points[0] };
	//int nsize[1];
	//nsize[0] = size;
	*im = imread("./Image/person_259.jpg", CV_LOAD_IMAGE_COLOR);
	polylines(*im, &points, &size, 1, true, Scalar(0, 255, 0)); 
	imshow("Original", *im);
	free(points);
}

void checkIn(Mat* im,int x , int y)
{
	int crosses = 0;
	Point* points;
	points = (Point*)calloc(lists->size, sizeof(pointList));
	ListToArray1(lists, points);
	int i, j;
	for (i = 0; i < lists->size; i++)
	{
		j = (i + 1) % lists->size;
		if ((points[i].y > y) != (points[j].y > y)) // �� ��ǥ(������)�� y��ǥ�� ���� ��ǥ�� ������ ��츸 Ȯ��
		{
			double atX = (points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x;
			if (x <= atX)
				crosses++;
		}
	}
	if (crosses % 2 == 1)
	{
		printf("��������\n");
	}
	else
	{
		printf("�ܺ�����\n");
	}
}

void delay(clock_t sec)
{
	clock_t start = clock();
	while (clock() - start < sec);
}