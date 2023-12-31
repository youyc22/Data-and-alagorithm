//此题有很简便的方法，不用建树，不过我懒得写了
#include <stdio.h>
#include <queue>
#include <stack>
#pragma warning(disable:4996)

struct TreeNode 
{
    char type;//0代表根节点，1代表普通节点，2代表缺损节点
    long long value;//节点的值
    TreeNode* father;
    TreeNode* leftkid;
    TreeNode* rightkid;
    TreeNode(long long val) : type(1),value(val), leftkid(nullptr), rightkid(nullptr), father(nullptr) {}
    ~TreeNode(){}
    void setType(char t)//改变节点的类型
    {
        type = t;
    }
};

void getPath(TreeNode* node,long long number)//获得路径
{
    std::stack<long long> nnn;//存储路径
    TreeNode* current = node;
    long long minus = number - current->value;
    while (current->value > 1)
    {
        while (current->type > 0)
        {
            nnn.push(minus + current->value);
            minus /= 2;
            current = current->father;
        }
        if (current->value == 1)
        {
            nnn.push(1);
            break;
        }
        minus = current->value + minus - current->father->value;
        current = current->father;
    }
    while (!nnn.empty())
    {
        printf("%lld ", nnn.top());
        nnn.pop();
    }
    printf("\n");
}
int main()
{
    long long N, M;
    long long number = 1;//当前的节点值
    long long missNum = 0, targetNum = 0;//缺失节点和目标节点的下标
    long long prev, sum, minus, final = 0;
    char flag = 0;//用于处理右孩子为缺失的特殊情况
    TreeNode* swapp = new TreeNode(0);//同上
    scanf("%lld %lld", &N, &M);
    long long* missingNodes = new long long[N];
    for (long long i = 0; i < N; i++) {
        scanf("%lld", &missingNodes[i]);
    }
    long long* targetNodes = new long long[M];
    for (long long i = 0; i < M; i++) {
        scanf("%lld", &targetNodes[i]);
    }
    TreeNode* root = new TreeNode(number);//根节点
    root->setType(0);//修改类型为根节点
    if (missNum < N && number == missingNodes[missNum])//如果第一个缺损点是1的情况
    {
        while (targetNum < M)
        {
            if (targetNodes[targetNum] == 1)
            {
                printf("%lld\n", 1);
                targetNum++;
                continue;
            }
            printf("%lld\n", 0);
            targetNum++;
        }
        return 0;
    }
    if (number == targetNodes[targetNum])//第一个目标节点为1的情况
    {
        printf("%lld\n", 1);
        targetNum++;
    }
    number++;
    std::queue<TreeNode*> ptrs;//用于更新树节点的队列
    ptrs.push(root);
    TreeNode* currentNode = root;//当前行、且属于当前子树的节点，用于计算路径
    while (targetNum < M)
    {
        //清除队列中的缺损节点
        while (!ptrs.empty() && ptrs.front()->type == 2)
        {
            ptrs.pop();
        }
        //树无法继续延伸，输出0
        if (ptrs.empty())
        {
            while (targetNum < M)
            {
                printf("0\n");
                targetNum++;
            }
            break;
        }
        //对于左孩子节点
        ptrs.front()->leftkid = new TreeNode(number);//创建
        ptrs.front()->leftkid->father = ptrs.front();//连接父节点
        ptrs.push(ptrs.front()->leftkid);//加入队列
        if (targetNum < M && number == targetNodes[targetNum])//如果是目标节点
        {
            getPath(ptrs.front()->leftkid, number);
            targetNum++;
        }
        if (missNum < N && number == missingNodes[missNum])//如果是缺损节点
        {
            missNum++;
            ptrs.front()->leftkid->setType(2);//改变类型
        }
        currentNode = ptrs.front()->leftkid;//更新当前节点
        number++;
        //对于右孩子节点
        ptrs.front()->rightkid = new TreeNode(number);//创建
        if (targetNum < M && number == targetNodes[targetNum])
        {
            getPath(currentNode, number);
            targetNum++;
        }
        if (missNum < N && number == missingNodes[missNum])//
        {
            flag = 1;
            ptrs.front()->rightkid->setType(1);//先设定为1，本次循环结束后再修改为2
            swapp = ptrs.front()->rightkid;
            ptrs.push(ptrs.front()->rightkid);//加入队列
            missNum++;
        }
        else
        {
            if (ptrs.front()->leftkid->type == 2)//左孩子为缺损，右孩子非缺损时，修改类型为根节点
            {
                ptrs.front()->rightkid->setType(0);
                ptrs.front()->rightkid->father = currentNode;
                ptrs.push(ptrs.front()->rightkid);
            }
        }
        number++;
        //对于未存入树中的节点
        prev = ptrs.front()->value;
        minus = 0;
        ptrs.pop();
        while (ptrs.front()->type == 2)
        {
            minus++;
            ptrs.pop();
        }
        sum = ptrs.front()->value - prev - minus - 1;//计算ptrs中两个非缺损节点之间的差值（同时减去了缺损节点的数量）
        final = number + sum * 2;//下一个currentNode的左孩子的值
        if (flag)
        {
            if (sum && (missNum >= N || (missNum < N && number != missingNodes[missNum])))
            {
                TreeNode* newRoot = new TreeNode(number);
                newRoot->setType(0);
                newRoot->father = currentNode;
                ptrs.push(newRoot);
            }
        }//判断number到final之间是否有缺损节点或目标节点
        while ( targetNum < M && targetNodes[targetNum] < final )
        {
            number = targetNodes[targetNum];
            getPath(currentNode, number);
            targetNum++;
        }
        while (missNum < N && missingNodes[missNum] < final)
        {
            number = missingNodes[missNum];
            if (number + 1 < final)
            {
                if (missNum + 1 < N && number + 1 == missingNodes[missNum + 1])//两个以上缺损节点连续的情况
                {
                    TreeNode* sw = new TreeNode(number);
                    sw->setType(2);
                    ptrs.push(sw);
                    missNum++;
                    continue;
                }
                else
                {
                    TreeNode* newRoot = new TreeNode(number + 1);//创建新根节点
                    newRoot->setType(0);
                    newRoot->father = currentNode;//下一个子树的根节点的父节点是上一个子树最后一个节点
                    TreeNode* sw = new TreeNode(number);//存储缺损节点
                    sw->setType(2);
                    ptrs.push(sw);
                    ptrs.push(newRoot);
                }
            }
            else
            {
                TreeNode* sw = new TreeNode(number);
                sw->setType(2);
                ptrs.push(sw);
            }
            missNum++;
        }
        if (flag)
        {
            swapp->setType(2);
            flag = 0;//修改节点类型为缺损节点
        }
        number = final;//更新number的值
    }
    return 0;
}
