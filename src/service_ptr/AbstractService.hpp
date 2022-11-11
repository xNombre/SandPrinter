#pragma once

class AbstractService {
    virtual bool init_service() = 0;
    
    virtual ~AbstractService() = 0;
};