#ifndef SERVICELOCATOR_H__
#define SERVICELOCATOR_H__

struct ServiceLocator
{
	ServiceLocator() {}
	~ServiceLocator() {}

	ServiceLocator(const ServiceLocator&) = delete;
	ServiceLocator& operator=(const ServiceLocator&) = delete;
	ServiceLocator(ServiceLocator&&) = delete;
	ServiceLocator& operator=(ServiceLocator&&) = delete;
};

#endif
