# Syslog Kayıtlarının Bağlı Liste ile Saklanması

Bu proje, Linux işletim sisteminde **syslog günlüklerini** okumak ve işlemek için **tek yönlü bağlı liste (singly linked list)** veri yapısını kullanarak bir uygulama geliştirmektedir.

## 📌 Proje Açıklaması

Linux sistem günlükleri (`/var/log/syslog`), sistem olaylarını ve hataları kaydetmek için kullanılır.  
Bu projede, **syslog kayıtları bir bağlı liste yapısında saklanarak** dinamik bellek yönetimi sağlanmaktadır.

## 📂 İçindekiler

- [Syslog Nedir?](#syslog-nedir)
- [Bağlı Liste Kullanım Nedeni](#bağlı-liste-kullanım-nedeni)
- [Kullanılan Bağlı Liste Türü](#kullanılan-bağlı-liste-türü)
- [Kod Açıklaması](#kod-açıklaması)
- [Kurulum ve Çalıştırma](#kurulum-ve-çalıştırma)
- [Örnek Çıktı](#örnek-çıktı)
- [Lisans](#lisans)

---

## 🔍 Syslog Nedir?

Syslog, Linux sistemlerinde **çekirdek, sistem servisleri ve uygulamalar tarafından üretilen logları merkezi olarak saklayan** bir günlükleme mekanizmasıdır.

**Kayıtların tutulduğu dosyalar:**
- **Genel loglar:** `/var/log/syslog`
- **Güvenlik logları:** `/var/log/auth.log`
- **Kernel logları:** `/var/log/kern.log`

### ✅ Kullanım Alanları
- **Hata ayıklama (debugging)**
- **Sistem güvenliğini izleme**
- **Performans analizi ve ağ takibi**

---

## 📌 Bağlı Liste Kullanım Nedeni

Syslog kayıtları **dinamik olarak büyüyen** verilerdir.  
Bağlı liste kullanarak:
- **Bellek yönetimini esnek hale getiriyoruz.**
- **Yeni kayıtları hızlıca ekleyebiliyoruz.**
- **Dizilere göre daha verimli ve esnek bir yapı sağlıyoruz.**

---

## 🔗 Kullanılan Bağlı Liste Türü

Bu projede **tek yönlü bağlı liste (singly linked list)** kullanılmıştır.

### ❓ **Neden Tek Yönlü Bağlı Liste Seçildi?**
✔️ **Syslog kayıtları yalnızca eklenir ve ileriye doğru okunur.**  
✔️ **Bellek kullanımını optimize eder, çift yönlü listeye göre daha az yer kaplar.**  
✔️ **Eklemeler hızlıdır, sadece listenin sonuna eklenir.**  

### 🚫 **Diğer Türler Neden Kullanılmadı?**
❌ **Çift yönlü bağlı liste (Doubly Linked List):**  
- Fazladan `prev` pointer kullanımı bellek tüketimini artırır.  
- Syslog için geriye dönük erişim ihtiyacı yoktur.  

❌ **Döngüsel bağlı liste (Circular Linked List):**  
- Syslog kayıtları sürekli döngü içinde işlenmez, baştan sona okunur.  

---

## 📌 Kod Açıklaması

Program, `/var/log/syslog` dosyasını okuyarak her satırı bir **bağlı liste düğümü** olarak saklar.

### 🛠️ **Fonksiyonlar**
- **`createNode(char *logData)`** → Yeni bir düğüm oluşturur.  
- **`append(struct Node **head, char *logData)`** → Yeni bir log ekler.  
- **`printList(struct Node *head)`** → Syslog kayıtlarını ekrana yazdırır.  
- **`freeList(struct Node *head)`** → Bellek sızıntısını önlemek için listeyi temizler.  

---

## 🚀 Kurulum ve Çalıştırma

### 📥 1. Derleme
```bash
gcc syslog_linked_list.c -o syslog_reader
