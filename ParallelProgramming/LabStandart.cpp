namespace pp_lbst
{
	const size_t NTHREAD = 4;
	const size_t COUNT = 100;

	class lbst
	{
	public:

		int array[COUNT] = { 1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1 };

		bool alter_sign(int array[])
		{
			bool res = true;
			int size = COUNT;
			int i = 1;
			do
			{
				res = array[i - 1] > 0 ? array[i] < 0 : array[i];
				++i;
			} while (i < size && res);
			return res;
		}
	};
}