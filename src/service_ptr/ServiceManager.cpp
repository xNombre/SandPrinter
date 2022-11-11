/*#include "ServiceManager.hpp"



ServiceManager::~ServiceManager()
{
    
}

std::shared_ptr<ServiceManager> ServiceManager::get_instance()
{
    if (!ptr) {
        ptr = std::make_shared<ServiceManager>();
    }

    return ptr;
}

template <typename Service>
std::shared_ptr<AbstractService> ServiceManager::get_service()
{
    if (!services_map[service]) {
        services_map[service] = std::make_shared<Service>();
    }
    
    return services_map[service];
}

void ServiceManager::start_services()
{
    
}*/

