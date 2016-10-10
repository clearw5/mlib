
一个常用数据结构和工具的库。
本库未完善。当前仅包括本次项目需要内容。以下以及代码中标记TODO的是等待完成的。但不影响正常使用。
包括：
	1.m_allocator 内存池。用于尽量减少内存泄漏和内存碎片(TODO)。并且提供一种避免C语言中先分配内存再传入指针最后释放参数的参数传递的方法。以及统一回收内存的工具。
		m_allocator使用一个set（当前使用hash_set作为实现）记录所有由他分配的指针，并在生命周期结束时统一释放。
		本库中很多操作依赖于内存池。
		例如以往要初始化一个结构体指针可能是这样的：
		something *ptr = (something*)malloc(sizoef(something));
		something_init(ptr);
		//do something
		free(ptr);
		使用m_allocator后的代码将是这样的：
		m_allocator tmp = m_allocator_new();
		something *ptr = something_new(tmp);
		//dosomthing
		m_allocator_destory(&tmp);
		这看起来貌似没什么区别。但在指针和临时分配内存很多的时候方便很多。你可以不那么再小心翼翼地提醒自己free，只要销毁对应的内存池即可。
		甚至不需要再为每个结构体写一个free函数。
	2.常用数据结构接口。目前包括m_set(集合), m_map(映射), m_list(列表),m_iterator(迭代器), deque（双端队列）（TODO）, queue（队列），stack（栈）。
	  这些数据结构都是带有严格类型检查的泛型结构。每个容器可以存取不同类型的元素但取出时会进行类型检查。
	  但不建议在除了map以外的容器存取不同的类型。
	  这些数据结构包括或将包括以下实现：
	  m_set: m_hash_set（哈希表），m_tree_set（二叉树实现的集合）（TODO），m_linked_list（链表实现的线性表），m_skip_map（跳表）（TODO）
	  m_list: m_linked_list （链表），m_vector（变长数组）
	  m_map: m_hash_map（哈希表），m_tree_set（红黑树实现的map）(TODO)，m_skip_map（跳表实现的map）(TODO), m_linear_map（vector实现的线性表）
	  m_iterator: 各种容器对应的迭代器
	  deque，queue，stack：m_linked_list, m_vector 
	   由于这些数据结构的设计，你可以像C++的虚基类和Java, C#的interface一样使用它们。
	   例如在某个项目中一开始使用了红黑树作为set的实现，后来由于需求更改需要以空间换取时间从而需要使用哈希表，那么只需要修改一个语句：
	   将 m_set s = m_tree_set_new_set() 改为m_set s = m_hash_set_new_set() 即可。由于C语言不支持重载，这将是非常有用的，不需要修改所有调用的函数名即可更改实现。
	3.以上数据结构的基础：m_element（元素），m_element可以存取不同类型的数据并保存有其数据类型（m_type），不会有类型丢失问题。
	4.m_string（字符串），m_array（数组），m_byte_stream（字节流）以及数据序列化，m_stream（流）(TODO)，m_string_stream（字符串流）(TODO)
	  m_except（异常。不同于C++的异常。这里只是一个错误报告与处理工具）。
	5.m_random（随机数），m_timer（计时器），m_time（日期时间），m_log（日志工具）等常用工具