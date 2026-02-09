*This project has been created as part of the 42 curriculum by ybalkan.*

---

#   Libft: Bir C Programcısının Günlüğü
##  Proje Hakkında (Description)

**Libft**, benim 42 okulundaki ilk büyük projemdi. C dilinin standart kütüphanesini (`libc`) kullanmamız yasaklandığında, aslında bize bir kütüphane değil, **bilgisayarın nasıl çalıştığı** öğretiliyordu.

Bu proje, hazır fonksiyonları (`printf`, `strcpy` vb.) kullanmak yerine, onların arkasındaki mühendisliği, bellek (RAM) yönetimini ve veri yapılarını sıfırdan inşa etme sürecimdir. 

Aşağıdaki satırlar, bu kütüphaneyi geliştirirken tuttuğum notların, karşılaştığım `Segfault` hatalarının ve çözümlediğim algoritmaların bir derlemesidir.

---

##  Geliştirme Günlüğü (Dev Log)

Bu projeyi tek oturuşta yazmadım; sancılı ama öğretici bir 4 haftalık süreçti. İşte aşama aşama yaşadıklarım:

###  Hafta 1: Pointerlarla İlk Temas (The Awakening)
Projeye ilk başladığımda `ft_memset` ve `ft_bzero` gibi basit hafıza fonksiyonlarıyla ısındım. Ancak pointer aritmetiği kafamı karıştırdı.
* **Sorun:** `void *` pointer ile aritmetik işlem yapılamayacağını (`p++` diyemezsin) öğrendiğimde kodlarım patladı.
* **Çözüm:** Belleğin bayt bayt işlendiğini kavradım. Herhangi bir adresi `(unsigned char *)` türüne "cast" ettiğimde, hafızada 1 baytlık adımlarla gezebiliyordum. Bu benim için bir dönüm noktasıydı.

###  Hafta 2: String Manipülasyonu ve '\0' Tuzağı
`ft_strlcpy` ve `ft_strlcat` fonksiyonları, güvenlik (buffer overflow) açısından kritikti.
* **Ders:** C dilinde string diye bir şey yok, sadece sonu `\0` (Null Terminator) ile biten karakter dizileri var. Bir döngüde `\0` koymayı unuttuğum için programın hafızadaki rastgele verileri (garbage value) okuyup çökmesi, bana bu karakterin "dur" tabelası olduğunu öğretti.

###  Hafta 3: Dinamik Bellek ve Malloc (The Nightmare)
`ft_split` fonksiyonu... Muhtemelen projenin en zor kısmıydı.
* **Zorluk:** Bir cümleyi kelimelere bölerken, her kelime için Heap'ten (`malloc`) yer ayırmam gerekiyordu.
* **Kırılma Anı:** 3. kelimeyi ayırırken hafıza dolarsa ne olacak? Geriye dönüp önceki 2 kelimeyi de `free` etmem gerektiğini fark ettim. "Memory Leak" kavramıyla burada tanıştım. Açtığın her parantezi kapatmak gibi, ayırdığın her belleği temizlemek zorundasın.

###  Hafta 4: Part 3 ve Veri Yapıları (Linked Lists)
Diziler (Array) iyiydi ama esnek değildi. PDF'in son bölümü (Part 3) ile **Bağlı Listelere** geçiş yaptım.
* **Analoji:** Bunu bir tren vagonuna benzettim. Her vagon (Node), hem kendi yükünü taşıyor hem de arkasındaki vagonun kancasını (adresini) tutuyor. Araya vagon eklemek için tüm treni yeniden yapmaya gerek yok, sadece kancaları değiştirmek yetiyor. Bu yapı, veri yönetimine bakış açımı değiştirdi.

---

##  Teknik Notlarım ve Analojiler

Kodlarken soyut kavramları somutlaştırmak için kendime şu notları aldım:

### 1. "Ev ve Adres Defteri" (Pointer Mantığı)
Pointerları anlamak için bu analojiyi kullandım:

| Kavram | Temsili | Açıklama |
| :--- | :--- | :--- |
| `char c = 'Y';` | **Yusuf'un Evi** | İçinde 'Y' eşyası olan fiziksel yapı. |
| `&` | **Konum** | Evin sokak adresi (Örn: 0x7ffe...). |
| `char *p = &c;` | **Adres Defteri** | Adresi not ettiğim kağıt. |

* `p` dediğimde: Evi değil, kağıttaki adresi kastederim.
* `*p` dediğimde: "O adrese git ve kapıyı aç" derim.

### 2. Hafıza Haritası (Memory Map)
`char *s = "YBALKAN";` tanımladığımda RAM'de aslında ne oluyor?

| 'Y' | 'B' | 'A' | 'L' | 'K' | 'A' | 'N' | '\0' |
| :---: | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 1000 | 1001 | 1002 | 1003 | 1004 | 1005 | 1006 | 1007 |

* `*(s + 3)` komutu bilgisayara: "Başlangıçtan (1000) 3 adım git (1003) ve oradaki değeri ('L') getir" der.

---

##  Kütüphane İçeriği

Proje PDF'ine uygun olarak fonksiyonları 3 ana kategoriye ayırdım:

###  Part 1: Libc Fonksiyonları
Standart kütüphanenin birebir replikaları.
* **Memory:** `ft_memset`, `ft_bzero`, `ft_memcpy`, `ft_memmove`, `ft_memchr`, `ft_memcmp`, `ft_calloc`, `ft_strdup`.
* **String:** `ft_strlen`, `ft_strlcpy`, `ft_strlcat`, `ft_strchr`, `ft_strrchr`, `ft_strnstr`, `ft_strncmp`.
* **Type:** `ft_atoi`, `ft_isalpha`, `ft_isdigit`, `ft_isalnum`, `ft_isascii`, `ft_isprint`, `ft_toupper`, `ft_tolower`.

###  Part 2: Ek Fonksiyonlar
Standartta olmayan ama hayat kurtaran araçlar.
* `ft_substr` (Parça al), `ft_strjoin` (Birleştir), `ft_strtrim` (Kırp).
* `ft_split` (Parçala/Dizi yap), `ft_itoa` (Sayıyı yazıya çevir).
* `ft_strmapi`, `ft_striteri` (Fonksiyon uygula).
* `ft_putchar_fd`, `ft_putstr_fd`, `ft_putendl_fd`, `ft_putnbr_fd` (Dosya yazdırma).

###  Part 3: Bağlı Listeler (Linked Lists)
`t_list` struct yapısı üzerine kurulu veri yönetimi.
* `ft_lstnew` (Yeni düğüm), `ft_lstadd_front` (Başa ekle), `ft_lstadd_back` (Sona ekle).
* `ft_lstsize` (Boyut), `ft_lstlast` (Son düğüm).
* `ft_lstdelone` (Sil), `ft_lstclear` (Temizle), `ft_lstiter` (Dolaş), `ft_lstmap` (Kopyala).

##  Kütüphane İçeriği (Detailed Functions)

Aşağıda `libft.h` başlık dosyasında prototipleri bulunan tüm fonksiyonların kategorize edilmiş listesi bulunmaktadır.

###  Bellek Yönetimi (Memory Manipulation)
RAM üzerindeki ham baytları işleyen fonksiyonlar.
* `ft_memset`: Bellek alanını sabit bir bayt ile doldurur.
* `ft_bzero`: Bellek alanını sıfırlar (tüm baytları `\0` yapar).
* `ft_memcpy`: Bellek alanını kopyalar (örtüşme koruması yoktur).
* `ft_memmove`: Bellek alanını kopyalar (örtüşme korumalıdır, güvenlidir).
* `ft_memchr`: Bellek bloğunda belirli bir karakteri arar.
* `ft_memcmp`: İki bellek bloğunu karşılaştırır.
* `ft_calloc`: `malloc` gibi yer ayırır ancak ayrılan yeri sıfırlar.

###  String İşlemleri (String Manipulation)
C tipi null-terminated stringler üzerinde işlemler.
* `ft_strlen`: String uzunluğunu hesaplar.
* `ft_strlcpy`: Güvenli string kopyalama (boyut kontrollü).
* `ft_strlcat`: Güvenli string birleştirme.
* `ft_strchr`: String içinde karakter arar (ilk eşleşme).
* `ft_strrchr`: String içinde karakter arar (son eşleşme).
* `ft_strnstr`: String içinde başka bir string arar (sınırlandırılmış).
* `ft_strncmp`: İki stringi belirli bir boyuta kadar karşılaştırır.
* `ft_strdup`: Stringin bir kopyasını heap üzerinde (malloc ile) oluşturur.
* `ft_substr`: Stringden bir alt parça (substring) alır.
* `ft_strjoin`: İki stringi birleştirip yeni bir string döndürür.
* `ft_strtrim`: Stringin başındaki ve sonundaki istenmeyen karakterleri budar.
* `ft_split`: Bir stringi belirli bir ayırıcıya (delimiter) göre bölüp diziye dönüştürür.
* `ft_strmapi`: Bir stringin her karakterine fonksiyon uygular ve yeni string oluşturur.
* `ft_striteri`: Bir stringin her karakterine fonksiyon uygular (yerinde değişiklik).

###  Tip Dönüşümü ve Kontrol (Type & Conversion)
Karakter analizi ve sayısal dönüşümler.
* `ft_isalpha`, `ft_isdigit`, `ft_isalnum`: Harf, rakam veya alfanümerik kontrolü.
* `ft_isascii`, `ft_isprint`: ASCII ve yazdırılabilir karakter kontrolü.
* `ft_toupper`, `ft_tolower`: Harf büyüklüğü dönüşümü.
* `ft_atoi`: Stringi tam sayıya (integer) çevirir.
* `ft_itoa`: Tam sayıyı stringe çevirir.

###  Dosya Yazdırma (File Descriptor Output)
Dosya tanımlayıcıları (fd) kullanarak çıktı verme işlemleri.
* `ft_putchar_fd`: Karakter yazdırır.
* `ft_putstr_fd`: String yazdırır.
* `ft_putendl_fd`: String yazdırır ve sonuna satır sonu ekler.
* `ft_putnbr_fd`: Sayı yazdırır.
* `ft_putptr_fd`: Pointer adresini (hexadecimal) yazdırır.

###  Bağlı Listeler (Linked Lists - Bonus)
`t_list` yapısı ile dinamik veri yönetimi.
* `ft_lstnew`: Yeni bir düğüm (node) oluşturur.
* `ft_lstadd_front`: Listeye baştan eleman ekler.
* `ft_lstadd_back`: Listeye sondan eleman ekler.
* `ft_lstsize`: Listenin eleman sayısını döndürür.
* `ft_lstlast`: Listenin son elemanını döndürür.
* `ft_lstprint`: Liste içeriğini yazdırır (Debug amaçlı).
* `ft_lstdelone`: Tek bir düğümü siler ve belleği temizler.
* `ft_lstclear`: Tüm listeyi siler ve temizler.
* `ft_lstiter`: Listenin her elemanına bir fonksiyon uygular.
* `ft_lstmap`: Listeyi kopyalar ve her elemana fonksiyon uygulayarak yeni liste oluşturur.

---
##  Kaynaklar
##  AI Kullanımı (AI Usage)

Bu projenin geliştirilmesi sırasında Yapay Zeka (AI) araçları, bir "öğretmen" ve "kod inceleme partneri" olarak kullanılmıştır. Kodun tamamı tarafımca yazılmış olup, AI aşağıdaki alanlarda destekleyici rol oynamıştır:

1.  **Kavramsal Anlama:** Pointer aritmetiği, `void *` casting ve Memory Leak gibi karmaşık konseptlerin analojilerle (Örn: Tren vagonu) somutlaştırılması.
2.  **Debugging ve Hata Analizi:** Özellikle `Segfault` hatalarında, hatanın kaynağını (bellek taşması, null pointer erişimi vb.) tespit etmek için GDB çıktıları analiz ettirilmiştir.
3.  **Dokümantasyon:** Fonksiyonların `man` sayfalarındaki teknik dilin sadeleştirilmesi ve bu README dosyasının, özellikle "Geliştirme Günlüğü" kısmının hikayeleştirilmesi.
4.  **Test Senaryoları:** `ft_split` gibi karmaşık fonksiyonlar için sınır durumların (edge cases) belirlenmesi (Örn: "Ardışık ayırıcılar gelirse ne olur?").

---

##  Talimatlar (Instructions)

### Derleme (Compilation)
Makefile dosyam, projenin tüm bölümlerini (Part 1, 2 ve 3) derleyecek şekilde yapılandırılmıştır.

Terminalde şu komutları kullanabilirsiniz:

```bash
git clone [https://github.com/ybalkan/libft.git](https://github.com/ybalkan/libft.git)
cd libft

# Tüm kütüphaneyi (Linked List dahil) derler:
make

# Derleme dosyalarını (.o) temizler:
make clean

# Projeyi tamamen sıfırlar:
make fclean

# Sıfırdan tekrar derler:
make re