package main

import (
	"encoding/json"
	"log"
	"net/http"
	"os"

	"github.com/google/uuid"
)

var gsessionmgr SessionMgr

func main() {
	// 设置路由处理函数
	http.HandleFunc("/login", withCORS(onLogin))
	http.HandleFunc("/getinfo", withCORS(withAuth(onGetInfo)))

	// 启动HTTP服务器
	err := http.ListenAndServe(os.Args[1], nil)
	if err != nil {
		log.Fatalln(err)
	}
}

// 带有CORS支持的中间件函数
func withCORS(handler http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		// 设置CORS头部，允许所有来源访问
		w.Header().Set("Access-Control-Allow-Origin", "*")
		w.Header().Set("Access-Control-Allow-Methods", "*")
		w.Header().Set("Access-Control-Allow-Headers", "*")
		w.Header().Set("Access-Control-Max-Age", "3600")

		// 处理预检请求
		if r.Method == "OPTIONS" {
			w.WriteHeader(http.StatusOK)
			return
		}

		// 调用实际的处理函数
		handler(w, r)
	}
}

// Auth认证的中间件函数
func withAuth(handler http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		// 调用实际的处理函数
		uid := r.Header.Get("QUUID")
		if !gsessionmgr.IsValid(uid) {
			w.WriteHeader(http.StatusUnauthorized)
			return
		}
		handler(w, r)
	}
}

func onGetInfo(w http.ResponseWriter, r *http.Request) {
	w.Header().Set("Content-Type", "application/json")
	var rsp struct {
		Code int    `json:"code"`
		Msg  string `json:"message"`
		UUID string `json:"uuid"`
	}
	rsp.Code = 200
	rsp.Msg = "测试成功"
	json.NewEncoder(w).Encode(&rsp)
}

func onLogin(w http.ResponseWriter, r *http.Request) {
	var user struct {
		User string `json:"username"`
		Pass string `json:"password"`
	}
	if err := json.NewDecoder(r.Body).Decode(&user); err != nil {
		log.Println(err)
		http.Error(w, "parse request json failed", http.StatusBadRequest)
		return
	}
	w.Header().Set("Content-Type", "application/json")
	var rsp struct {
		Code int    `json:"code"`
		Msg  string `json:"message"`
		UUID string `json:"uuid"`
	}
	if user.User != "admin" || user.Pass != "123456" {
		rsp.Code = 401
		rsp.Msg = "用户名或密码无效"
		json.NewEncoder(w).Encode(&rsp)
		return
	}
	rsp.Code = 200
	rsp.Msg = "登录成功"
	rsp.UUID = uuid.New().String()
	gsessionmgr.AddSession(rsp.UUID)
	json.NewEncoder(w).Encode(&rsp)
}
