package main

import (
	"sync"
	"time"
)

type SessionMgr struct {
	mutex    sync.Mutex
	sessions map[string]int64
}

func (mgr *SessionMgr) AddSession(uuid string) {
	now := time.Now().Unix()
	mgr.mutex.Lock()
	if mgr.sessions == nil {
		mgr.sessions = make(map[string]int64)
	}
	mgr.sessions[uuid] = now
	mgr.mutex.Unlock()
}

func (mgr *SessionMgr) IsValid(uuid string) bool {
	mgr.mutex.Lock()
	_, ok := mgr.sessions[uuid]
	mgr.mutex.Unlock()
	return ok
}
