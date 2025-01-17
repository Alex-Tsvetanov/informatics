#include <vector>  // vector
#include <utility> // pair
#include <set>     // set
#include <list>    // list
#include <stack>   // stack
#include <queue>   // queue

using namespace std;

using vertexType = size_t;
typedef vector < vector < vertexType > > N;

template < typename W> class M:public vector < vector < pair < W, bool > > >
{
public:
	M () 
	{
		
	}
	void add (vertexType a, vertexType b, W c)
	{
		if (this -> size () < a)
			this -> resize (a + 1, vector < pair < W, bool > > ());
		if ((*this)[0].size () < b)
			for (vertexType i = 0 ; i < (*this).size () ; i ++)
				(*this)[i].resize (b + 1, pair < W, bool > (-1, false));
		(*this)[a][b] = make_pair (c, true);
	}
};

template < typename W > struct G
{
	static const W NOT_CREATED = -1;
	size_t size;
	void eraseEdge (vertexType a, vertexType b)
	{
		for (vector <vertexType>::iterator it = n [a].begin () ; it != n [a].end () ; it ++)
			if (*it == b)
			{
				n [a].erase (it);
				break;
			}
		w [a][b] = make_pair (W(), false);
	}

	G <W>& add2Edges (vertexType a, vertexType b, W c = W ())
	{
		cout << "(" << a << ", " << b << ") -> " << c << "\n";
		cout << "(" << b << ", " << a << ") -> " << c << "\n";
		return this->addEdge (a, b, c).addEdge (b, a, c);
	}

	G <W>& addEdge (vertexType a, vertexType b, W c = W ())
	{
		vertexType Max = max (a, b);
		if (Max < n.size ())
		{
			n [a].push_back (b);
			w [a][b] = make_pair (c, true);
		}
		else
		{
			n.resize (Max + 1, vector <vertexType> ());
			w.resize (Max + 1);
			for (vertexType i = 0 ; i < Max + 1 ; i ++)
			{
				w [i].resize (Max);
			}
		}
		this->size = Max + 1;
		return *this;
	}

	typedef M <W> T;
	N n;
	T w;

	bool edge(vertexType i, vertexType j) const
	{
		return (w[i][j].second);
	}

	W f(vertexType i, vertexType j) const
	{
		if (w[i][j].second == false)
			return NOT_CREATED;
		return w[i][j].first;
	}

	W f(pair <vertexType, vertexType> j) const
	{
		return w[j.first][j.second].first;
	}

	G ()
	{
		size = 0;
	}

	void convertTtoN ()
	{
		for (vertexType i = 0 ; i < w.size () ; i ++)
			for (vertexType j = 0 ; j < w [i].size () ; j ++)
			{
				if (w [i][j].second)
				{
					n [i].push_back (j);
				}
			}
	}

	G (N n, T w)
	{
		this -> n = n;
		this -> w = w;
		size = n.size ();
	}

	G (T w)
	{
		this -> w = w;
		convertTtoN ();	
		size = n.size ();
	}

	bool topological_sort (void func (vertexType), vector <vertexType> s = vector <vertexType> ()) const
	{
		if (s.size () == n.size ())
		{
			for (vertexType i = 0 ; i < s.size () ; i ++)
				func (i);
			return 1;
		}
		if (s.size () == 0)
			for (vertexType i = 0 ; i < n.size () ; i ++)
			{
				s.push_back (i);
				if (topological_sort (func, s))
				{
					return 1;
				}
				s.pop_back ();
			}
		else
			for (vertexType i = 0 ; i < n [s [s.size () - 1]].size () ; i ++)
			{
				s.push_back (n [s [s.size () - 1]][i]);
				if (topological_sort (func, s))
				{
					return 1;
				}
				s.pop_back ();
			}
	}

	int* dfs (vertexType s = 0ull, vertexType level = 0ull) const
	{
		bool* visited = new bool [n.size ()];
		int* levels = new int [n.size ()];
		for (size_t i = 0 ; i < n.size () ; i ++)
			levels [i] = -1;
		stack < pair < vertexType, vertexType > > st;
		st.push ({s, level});
		while (!st.empty ())
		{
			auto f = st.top (); st.pop ();
			levels [f.first] = f.second;
			for (auto& x : n [f.first])
				if (levels [x] == -1)
					st.push ({x, f.second + 1});
		}
		delete[] visited;
		return levels;
	}

	int* bfs (vertexType s = 0ull, vertexType level = 0ull) const
	{
		int* levels = new int [n.size ()];
		for (size_t i = 0 ; i < n.size () ; i ++)
			levels [i] = -1;
		queue < pair < vertexType, vertexType > > q;
		q.push ({s, level});
		while (!q.empty ())
		{
			auto f = q.front (); q.pop ();
			levels [f.first] = f.second;
			for (auto& x : n [f.first])
				if (levels [x] == -1)
					q.push ({x, f.second + 1});
		}
		return levels;
	}

	bool cycle () const
	{
		vertexType NO_PREVIOUS = -1;
		bool* visited = new bool [n.size ()];
		queue < pair < vertexType, vertexType > > q;
		q.push ({0, NO_PREVIOUS});
		while (!q.empty ())
		{
			auto f = q.front (); q.pop ();
			for (auto& x : n [f.first])
				if (f.second != x)
				{
					if (visited [x] == 0)
						q.push ({x, f.first});
					else
					{
						delete[] visited;
						return true;
					}
				}
		}
		delete[] visited;
		return false;
	}

private:
	template <typename T0, typename T1, typename T2, typename T3> void addEdgeHelper (vertexType v, T0& it, T1& itColor, T2& diffColor, T3& color)
	{
		if (*color [v] != *color [it->second [i]])
		{
			for (size_t j = 0 ; j < itColor [*color [v]]->second.size () ; j ++)
				it->second.push_back (itColor [*color [v]]->second [j]);
			diffColor.erase (itColor [*color [v]]);
			itColor [*color [v]] = itColor [*color [it->second [i]]];
			color [v] = color [it->second [i]];
		}
	}

	void MST(void func(vertexType, vertexType), G <W> startingGraph = G <W> ()) const
	{
		unsigned long long* colornum = new unsigned long long [size];
		unsigned long long** color = new unsigned long long* [size];
		list < pair <unsigned long long*, vector < vertexType > > > diffColor;
		list < pair <unsigned long long*, vector < vertexType > > >::iterator itColor [size];
		list < pair <unsigned long long*, vector < vertexType > > >::iterator curr;
		for (vertexType i = 0 ; i < size ; i ++)
		{
			colornum [i] = i;
			color [i] = &(colornum [i]);
			diffColor.push_back ({color [i], {i}});
			if (diffColor.size () == 1)
				curr = diffColor.begin ();
			itColor [i] = curr;
			if (diffColor.size () != 1)
				curr ++;
		}
		curr = diffColor.begin ();
		for (int i = 0 ; i < startingGraph.n.size () ; i ++)
		{
			for (auto& x : startingGraph.n [i])
				addEdgeHelper (x, curr, itColor, diffColor, color);
			curr ++;
		}
		while (diffColor.size () > 2)
		{
			for (auto it = diffColor.begin () ; it != diffColor.end () ; it ++)
			{
				const size_t Size = it -> second.size ();
				for (size_t i = 0 ; i < Size ; i ++)
				{
					vertexType v, b = 0;
					W Min;
					for (size_t j = 0 ; j < n [it -> second [i]].size () ; j ++)
					{
						if (*color [it->second [i]] != *color [n [it -> second [i]][j]])
						{
							if (b == 0)
							{
								v = n [it->second[i]][j];
								Min = f (it->second [i], n [it -> second [i]][j]);
								b = 1;
							}
							else
							{
								W h = f (it->second [i], n [it -> second [i]][j]);
								if (Min > h)
								{
									Min = h;
									v = n [it->second[i]][j];
								}
							}
						}
						else
						{
						}
					}
					if (b)
					{
						func (it->second [i], v);
						addEdgeHelper (v, it, itColor, diffColor, color);
					}
				}
			}
		}
		delete[] colornum;
		delete[] color;
	}

private:

	struct fun2
	{
		bool operator () (pair < W *, unsigned long long >i, pair < W *, unsigned long long >j)
		{
			if (*(i.first) == *(j.first))
				return i.second > j.second;
			return *(i.first) > *(j.first);
		}
	};

public:
	void dijikstra(
			void func (vertexType, W), 
			vertexType s = 0ll) const
	{
		set < pair < W *, vertexType >, fun2 > T_;
		W* d = new W [size];
		for (vertexType i = 0; i < size; i++)
			d[i] = f (s, i);
		d [s] = 0;
		for (vertexType i = 0; i < size; i++)
			T_.insert (make_pair (&d[i], i));
		while (T_.size () > 0)
		{
			//for (size_t i = 0 ; i < size ; i ++)
			//	cout << d [i] << " ";
			//cout << endl;
			//for (auto& x : T_)
			//	cout << *(x.first) << " ";
			//cout << endl;

			vertexType j = T_.begin ()->second;

			T_.erase (T_.begin());
			for (typename set < pair < W *, vertexType >, fun2 >::iterator it = T_.begin (); it != T_.end (); it ++)
			{
				vertexType i = it->second;
				if (edge (j, i))
					if (d [i] == NOT_CREATED or d [i] < (d [j] + f (j, i)))
					{
						d [i] = (d [j] + f (j, i));
						it = T_.erase (it);
						it --;
						T_.insert ({&(d [i]), i});
					}
			}
		}
		for (size_t i = 0; i < size; i++)
			if (i != s)
				func (i, d [i]);
			else
				func (s, 0);
		delete[] d;
	}
};
