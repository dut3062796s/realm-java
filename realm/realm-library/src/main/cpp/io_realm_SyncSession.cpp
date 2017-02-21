/*
 * Copyright 2016 Realm Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <jni.h>

#include "io_realm_SyncSession.h"
#include "objectserver_shared.hpp"

using namespace std;
using namespace realm;
using namespace sync;

JNIEXPORT void JNICALL
Java_io_realm_SyncSession_nativeRefreshAccessToken(JNIEnv *env, jobject, jstring localRealmPath,
                                                   jstring accessToken, jstring sync_realm_url) {
    TR_ENTER()
    try {
        JStringAccessor local_realm_path(env, localRealmPath);
        std::shared_ptr<SyncSession> session = SyncManager::shared().get_existing_session(local_realm_path);
        if (session) {
            JStringAccessor access_token(env, accessToken);
            JStringAccessor realm_url(env, sync_realm_url);
            session->refresh_access_token(access_token, realm::util::Optional<std::string>(realm_url));
        } else {
            realm::jni_util::Log::d("nativeRefreshAccessToken no active/inactive session found");
        }
    } CATCH_STD()
}