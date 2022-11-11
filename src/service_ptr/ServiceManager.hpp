#pragma once

#include <map>
#include <mutex>
#include <memory>

#include "AbstractService.hpp"

/*class ServiceManager {
    static std::shared_ptr<ServiceManager> ptr;

    std::map<ServiceList, std::shared_ptr<AbstractService>> services_map;
    
public:
    ServiceManager() { }
    ServiceManager(const ServiceManager &) = delete;
    ServiceManager operator=(const ServiceManager &) = delete;

    std::shared_ptr<ServiceManager> get_instance();

    template <typename Service>
    std::shared_ptr<AbstractService> get_service();
    
    void start_services();

    ~ServiceManager();
};*/
