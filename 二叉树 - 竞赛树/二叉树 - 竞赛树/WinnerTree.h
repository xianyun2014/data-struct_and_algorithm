
template <typename T>  class WinnerTree
{
public:
	WinnerTree(int num);
	bool init(T *arr);
	void play(int m, int n);
	void del(T& val);
private:
	int *w;
	T *data;
	int max_num;
};




template <typename T>   WinnerTree::WinnerTree(  )
{
}




template <typename T>  bool WinnerTree::init(T *arr, int num)
{
	if (num < 1)
		return false;
	max_num = num;
	w = new int[max_num];
	data = arr;

	int s;   //倒2层前节点数
	for (s = 1; 2*s < num; s *= 2)
		continue;

	int lownum = (max_num - s) * 2;

	for (int i = 2; i <= lownum; i += 2)
		play((s + i)/2, s + i - 1, s + i);

	if (max_num % 2)
		play((lownum + s)/2, (lownum + s)/2 + 1);

}
