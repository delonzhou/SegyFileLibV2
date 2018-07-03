#ifndef CACHE_H
#define CACHE_H

#include <memory>
#include <map>
#include <vector>
#include <list>
#include <algorithm>

class IObserver{
public:
	virtual void handleEvent() = 0;
};

class IObservable{
public:
	virtual void addObserver(IObserver* observer) = 0;
	virtual void removeObserver(IObserver* observer) = 0;
	virtual void notifyObservers() = 0;
};

template<class Key, class Value>
class ICache :public IObservable{
public:
	virtual void add(Key key, std::shared_ptr<Value> value) = 0;
	virtual std::shared_ptr<Value> remove(Key key) = 0;
	virtual std::shared_ptr<Value> get(Key key)const = 0;
	virtual bool hasElement(Key key)const = 0;
	virtual std::vector<Key> getElements()const = 0;
	virtual void clear() = 0;
	virtual size_t size()const = 0;

	virtual std::shared_ptr<Value> getDeleted(Key key)const = 0;
	virtual bool hasDeletedElement(Key key)const = 0;
	virtual std::vector<Key> getDeletedElements()const = 0;
	virtual size_t deletedSize()const = 0;
};

template <class Key, class Value>
class LruCache :public ICache<Key, Value>{
public:
	typedef std::shared_ptr<Value> ValuePtr;
private:
	std::map<Key, ValuePtr> data;
	std::map<Key, ValuePtr> deletedData;
	std::map<Key, size_t> priority;
	std::list<IObserver*> observers;
	size_t cacheSize, index;
public:
	LruCache(size_t cs = 100, size_t i = 0) :cacheSize(cs), index(i){}

	virtual void add(Key key, ValuePtr value){
		if (data.count(key)){
			ValuePtr val = data[key];
			data[key] = value;
			deletedData[key] = val;
			priority[key] = index++;
			notifyObservers();
			deletedData.clear();
		}
		else{
			data[key] = value;
			priority[key] = index++;
			if (data.size()>cacheSize){
				while (data.size() > cacheSize){
                    typename std::map<Key, size_t>::iterator it = std::min_element(priority.begin(), priority.end());
					deletedData[it->first] = data[it->first];
					data.erase(it->first);
					priority.erase(it->first);
				}
				notifyObservers();
				deletedData.clear();
			}
		}
	}

	virtual std::shared_ptr<Value> remove(Key key){
		std::shared_ptr<Value> val;
		if (data.count(key)){
			val = data[key];
			deletedData[key] = data[key];
			data.erase(key);
			priority.erase(key);
			notifyObservers();
			deletedData.clear();
		}
		return val;
	}

	virtual ValuePtr get(Key key) const {
		ValuePtr val;
		if (data.count(key))
			val = data.at(key);
		return val;
	}

	virtual bool hasElement(Key key)const{
		return data.count(key) > 0;
	}

	virtual std::vector<Key> getElements()const {
		std::vector<Key> keys;
        for (typename std::map<Key, ValuePtr>::const_iterator it = data.begin(); it != data.end(); ++it) {
			keys.push_back(it->first);
		}
		return keys;
	}

	virtual void clear(){
        for (typename std::map<Key, ValuePtr>::iterator it = data.begin(); it != data.end(); ++it) {
			deletedData[it->first] = it->second;
		}
		data.clear();
		priority.clear();
		notifyObservers();
		deletedData.clear();
	}

	virtual size_t size() const{
		return data.size();
	}

	virtual std::shared_ptr<Value> getDeleted(Key key)const{
		ValuePtr val;
		if (deletedData.count(key))val = deletedData.at(key);
		return val;
	}

	virtual bool hasDeletedElement(Key key)const{
		return deletedData.count(key) > 0;
	}

	virtual std::vector<Key> getDeletedElements()const{
		std::vector<Key> keys;
        for (typename std::map<Key, ValuePtr>::const_iterator it = deletedData.begin(); it != deletedData.end(); ++it) {
			keys.push_back(it->first);
		}
		return keys;
	}

	virtual size_t deletedSize()const{
		return deletedData.size();
	}

	virtual void addObserver(IObserver* observer){
		std::list<IObserver*>::iterator it = std::find(observers.begin(), observers.end(), observer);
        if (it == observers.end())
            observers.push_back(observer);
	}

	virtual void removeObserver(IObserver* observer) {
		std::list<IObserver*>::iterator it = std::find(observers.begin(), observers.end(), observer);
		observers.erase(it);
	}

	virtual void notifyObservers(){
		for (std::list<IObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
			(*it)->handleEvent();
		}
	}

};

#endif
