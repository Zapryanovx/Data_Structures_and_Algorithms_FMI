Крадаптирано от [тук](https://github.com/Stoyan-Zlatev/Data-Sructures-and-Algorithms/blob/main/Tips.md)

# Полезни трикове

#### Асинхронност на потоците за четене и писане

Тези два реда в началото на main функцията забързват значително входно-изходните потоци.
```c++
std::ios_base::sync_with_stdio(false);
std::cin.tie(nullptr);
```
Алтернативно може да се използва навсякъде printf / scanf за четене и писане, като те не бива да се смесват със cin / cout.

Също отпечатването на '\n' е по-бързо от std::endl, понеже второто flush-ва потока.

---

#### Timeout
Изпълняването на една програма няколко пъти, може да даде различни времена за изпълнение. Това е така заради натовареността на сървърите на Hackerrank.

#### Променливи в статичната памет
Колкото и лоша практика да е по принцип създаването на глобални променливи, тоест в статичната памет (не в стека или хийпа), е добро оптимизационно решение, а и създават удобство - заделянето на статична памет се случва пре-компилационно и не се добавя към времето за изпълнение на програмата, а големите ресурси са споделени.
Също така инициализацията на масив го запълва автоматично с `0`, съответстващо на
```c++
int array[10]{};
```

---

#### Една библиотека
Библиотеката 
```c++
#include <bits/stdc++.h>
```
съдържа най-често използване библиотеки и е достатъчно да включим нея, без да мислим коя библиотека ни липсва според нещата, които използваме. Може да я изтеглите от [github](<https://github.com/tekfyl/bits-stdc-.h-for-mac/blob/master/stdc%2B%2B.h>).

---


#### Проверки за четност
Стандартната проверка дали дадено цяло число е четно или не чрез оператора за делене с остатък
```c++
!(num % 2) // even
```
е по - бавна в сравнение с по - оптималната проверка за послеследния бит в двоичното представяне на числото чрез побитовия оператор "и"
```c++
!(num & 1) // even
```

#### Компилатори
Hackerrank работи с GCC компилатор, което дава някои ограничение / предимства през VCC:
- Липсва запазване на наредбата при употреба на `multimap` и `multiset` и др. (при VCC се запазва наредбата на добавянето на елементи).
- Има възможност за създаване на статичен масив с променлива дължина (при VCC задължително трябва да е динамичен масива).

- Hackerrank не харесва тернарен оператор при cout


#### Оптимизация за heap (приоритетна опашка)
Стандартният минимален хийп от наредени двойки, който може да се създаде като
```c++
std::priority_queue<std::pair<int,int>> pq;
```
е със значително по-лошо time complexity на операциите, в сравнения с този, при който експлицитно са указани имплементация и компаратор:
```c++
std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>, std::greater<std::pair<int,int>>> pq;
```

---

#### Стандартна имплементация на компаратор std::greater<<std::pair>>
Default-ната имплементация на компараторът за наредени двойки има следната имплементация:
```c++
template<typename T> struct greater {
        constexpr bool operator()(T const& a, T const& b) const {
            return a.first>b.first || ( (a.first<b.first) && (a.second>b.second));
        }
};
```
която при желание за създаване на минимален heap сортиращ по първата компонента, става неефективна заради допълнителното условие за втората компонента. Тогава е подходящо предефиниране на компаратор:
```c++
struct Greater{
    bool operator()(const std::pair<int,int>& first, const std::pair<int,int>& second ) const {
        return first.first > second.first;
    }
};
```

---
