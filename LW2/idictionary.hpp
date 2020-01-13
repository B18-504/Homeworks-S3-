#ifndef idictionary_h
#define idictionary_h

enum Color {RED, BLACK, DOUBLEBLACK};

template <typename TKey, typename TElement>
class IDictionary {
protected:
    int count; //кол-во элементов в словаре
public:
    virtual int getCount() const = 0; //получение кол-ва элементов
    virtual bool containsKey(const TKey& key) const = 0; //проверка нахождение элемента в словаре
    virtual void insert(const TKey& key, const TElement& item) = 0; //добавление элемента
    virtual void remove(const TKey& key) = 0; //удаление элемента
};

#endif
