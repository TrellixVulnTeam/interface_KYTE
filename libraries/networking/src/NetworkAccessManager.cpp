//
//  NetworkAccessManager.cpp
//  libraries/networking/src
//
//  Created by Clement on 7/1/14.
//  Copyright 2014 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#include "NetworkAccessManager.h"

#include <QThreadStorage>
#include <QtNetwork/QNetworkProxy>

#include "AtpReply.h"
#include "ResourceManager.h"

QThreadStorage<QNetworkAccessManager*> networkAccessManagers;

QNetworkAccessManager& NetworkAccessManager::getInstance() {
    if (!networkAccessManagers.hasLocalData()) {
        QNetworkAccessManager* networkAccessManager = new QNetworkAccessManager();
        auto resourceManager = DependencyManager::get<ResourceManager>();
        networkAccessManager->setCache(resourceManager->networkDiskCache);
        networkAccessManagers.setLocalData(networkAccessManager);
    }
    
    return *networkAccessManagers.localData();
}

QNetworkReply* NetworkAccessManager::createRequest(Operation operation, const QNetworkRequest& request, QIODevice* device) {
    if (request.url().scheme() == "atp" && operation == GetOperation) {
        return new AtpReply(request.url());
        //auto url = request.url().toString();
        //return QNetworkAccessManager::createRequest(operation, request, device);
    } else {
        return QNetworkAccessManager::createRequest(operation, request, device);
    }
}
