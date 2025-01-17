//
//  TivoliWebEngineProfile.h
//  interface/src/networking
//
//  Created by Stephen Birarda on 2016-10-17.
//  Copyright 2016 High Fidelity, Inc.
//
//  Distributed under the Apache License, Version 2.0.
//  See the accompanying file LICENSE or http://www.apache.org/licenses/LICENSE-2.0.html
//

#pragma once

#ifndef hifi_TivoliWebEngineProfile_h
#define hifi_TivoliWebEngineProfile_h

#include "ContextAwareProfile.h"

#if !defined(Q_OS_ANDROID)

class TivoliWebEngineProfile : public ContextAwareProfile {
    using Parent = ContextAwareProfile;
public:
    static void registerWithContext(QQmlContext* parent);

    static void clearCache();

protected:
    TivoliWebEngineProfile(QQmlContext* parent);
    virtual ~TivoliWebEngineProfile();

    class RequestInterceptor : public Parent::RequestInterceptor {
    public:
        RequestInterceptor(ContextAwareProfile* parent) : Parent::RequestInterceptor(parent) {}
        void interceptRequest(QWebEngineUrlRequestInfo& info) override;
    };
};

#endif

#endif // hifi_TivoliWebEngineProfile_h
