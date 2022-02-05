#include <iostream>
#include <thread>

namespace pp_lbthrd
{
	const size_t NTHREAD = 4;
	const size_t COUNT = 100;

	class lbthrd
	{
	public:

		int array[COUNT] = { 1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1,
		1, -2, 4, -6, 7, -8, 3, -4, 5, -6, 7, -5, 5, -8, 3, -2, 7, -4, 9, -1 };

		static void alter_sign(int* array, size_t left, size_t right, bool &res)
		{
			res = true;
			size_t i = left + 1;
			do
			{
				res = array[i - 1] > 0 ? array[i] < 0 : array[i];
				++i;
			} while (i < right && res);
		}

		int sign_parallel(int* array)
		{
			std::thread t[NTHREAD];
			size_t block_size = COUNT / NTHREAD;
			bool res[NTHREAD];
			for (size_t i = 0; i < NTHREAD; ++i)
			{
				if (i == NTHREAD - 1)
				{
					t[i] = std::thread(alter_sign, array, block_size * i, COUNT, std::ref(res[i]));
				}
				else
				{
					t[i] = std::thread(alter_sign, array, block_size * i, block_size * (i + 1) + 1, std::ref(res[i]));
				}
			}

			for (size_t i = 0; i < NTHREAD; ++i)
			{
				t[i].join();
			}

			bool global_res = true;
			for (size_t i = 0; i < NTHREAD; ++i)
			{
				global_res = global_res && res[i];
			}

			return global_res;
		}
	};
}