# ReverseShellExe

> Eğitim, araştırma ve yalnızca yazılı izin alınmış güvenlik testleri için hazırlanmıştır.

ReverseShellExe, ESP32-S2 Mini üzerinde USB HID klavye emülasyonu kullanarak Windows PowerShell otomasyonunu ve ters bağlantıların güvenlik açısından incelenmesini amaçlayan bir araştırma projesidir.

Bu repository, Windows üzerinde aşağıdaki davranışların laboratuvar ortamında analiz edilmesi için hazırlanmıştır:

- USB HID klavye emülasyonu
- PowerShell komut otomasyonu
- Türkçe ve İngilizce klavye düzenleri arasındaki uyumluluk
- Gizli PowerShell süreçlerinin güvenlik açısından incelenmesi
- Windows Görev Zamanlayıcı üzerinden kalıcılık davranışı
- SYSTEM hesabı altında çalışan görevlerin tespiti
- PowerShell tabanlı ters bağlantıların izlenmesi
- Olay müdahalesi ve savunma mekanizmaları

##  Önemli Uyarı

Bu proje mevcut haliyle aşağıdaki yüksek riskli davranışları içerebilir:

- Yönetici yetkisi isteyen PowerShell penceresi açma
- PowerShell penceresini gizleme
- İnternetten veya uzak bir Git deposundan dosya indirme
- PowerShell yürütme politikalarını atlama
- Windows Görev Zamanlayıcı ile oturum açılışında çalışan görev oluşturma
- SYSTEM hesabı altında kalıcılık oluşturma
- Uzak bir IP adresine TCP bağlantısı kurma
- Uzak taraftan alınan komutları PowerShell ile çalıştırma

Bu özellikler yalnızca sahibinin açık izni bulunan, izole edilmiş laboratuvar sistemlerinde test edilmelidir.

## Dosyalar

### `bad_usb.cpp`

ESP32-S2 Mini üzerinde çalışan USB HID klavye emülasyon bileşenidir.

Başlıca işlevleri:

- USB klavye olarak tanınma
- Windows Çalıştır penceresini açma
- PowerShell komutlarını klavye girdisi olarak gönderme
- Türkçe klavye düzenine uygun karakter dönüşümleri yapma
- Test betiklerini sırayla çalıştırma

`trPrint()` fonksiyonu; Türkçe klavye düzeninde nokta, iki nokta, eğik çizgi, ters eğik çizgi, alt çizgi ve benzeri karakterlerin HID üzerinden doğru gönderilmesi amacıyla kullanılmıştır.

## `change.ps1`

Windows kullanıcı dil ve klavye düzenlerini kontrol eden yardımcı PowerShell betiğidir.

Betiğin amacı:

1. Mevcut kullanıcı dil listesini almak
2. `en-US` dilinin bulunup bulunmadığını kontrol etmek
3. Gerekirse İngilizce dil paketini listeye eklemek
4. İngilizce Q klavye düzenini yapılandırmak
5. İngilizce klavyeyi varsayılan giriş yöntemi yapmak

Bu işlem, HID klavye girdilerinin Türkçe sistemlerde yanlış karakterlere dönüşmesini önlemek amacıyla kullanılmıştır.

## `prts.ps1`

PowerShell tabanlı TCP ters bağlantı bileşenidir.

Test ortamında:

1. Belirlenen uzak IP adresine bağlantı kurar.
2. TCP akışı üzerinden veri alır.
3. Alınan verileri PowerShell komutları olarak işler.
4. Komut çıktısını aynı bağlantı üzerinden geri gönderir.
5. Bağlantı sonlandırıldığında istemciyi kapatır.

Bu davranış, savunma araçlarının ters bağlantıları ve PowerShell tabanlı komut çalıştırma etkinliklerini nasıl tespit ettiğini incelemek amacıyla analiz edilmelidir.


## Güvenlik Araştırması Kapsamı

Bu proje aşağıdaki güvenlik konularını incelemek için kullanılabilir:

- BadUSB ve HID tabanlı saldırıların tespiti
- USB cihaz envanteri ve erişim politikaları
- PowerShell Script Block Logging
- PowerShell Process Creation olayları
- Gizli pencereyle başlayan süreçlerin tespiti
- `ExecutionPolicy Bypass` kullanımının izlenmesi
- Görev Zamanlayıcı değişikliklerinin denetlenmesi
- SYSTEM hesabıyla çalışan şüpheli görevler
- Şüpheli dış TCP bağlantıları
- Windows Defender ve EDR alarm kuralları

## Tespit Edilebilecek Göstergeler

Aşağıdaki davranışlar güvenlik izleme sistemlerinde incelenmelidir:

- `powershell.exe` işleminin gizli pencereyle çalıştırılması
- `-ExecutionPolicy Bypass` parametresi
- PowerShell üzerinden uzak dosya veya repository indirilmesi
- Kullanıcı oturum açılışında çalışan yeni görevler
- SYSTEM hesabıyla oluşturulan görevler
- Sistem dizinleri altında yeni PowerShell dosyaları
- Bilinmeyen IP adreslerine yapılan TCP bağlantıları
- USB üzerinden kısa sürede gönderilen yoğun klavye girdileri
- PowerShell’in `Invoke-Expression` benzeri dinamik komut çalıştırma davranışları

## Temizleme

Test bittikten sonra laboratuvar sisteminde aşağıdaki varlıklar kontrol edilmelidir:

- Oluşturulan Görev Zamanlayıcı görevleri
- Kopyalanan veya indirilen PowerShell dosyaları
- Değiştirilen klavye ve dil ayarları
- Açık PowerShell süreçleri
- Kalıcı ağ bağlantıları
- Güvenlik günlükleri ve test kayıtları

Sanal makine kullanılıyorsa test öncesi alınan temiz anlık görüntüye dönülmesi önerilir.

## Yayınlama Notu

Bu repository’ye gerçek sistemlere ait aşağıdaki bilgileri eklemeyin:

- Gerçek IP adresleri
- Gerçek kullanıcı adları
- Gerçek ağ bilgileri
- Üretim ortamı dosya yolları
- Erişim anahtarları veya parolalar
- Yetkisiz sistemlere ait günlükler
- Çalışan saldırı altyapısına ait bağlantı bilgileri

Özellikle `prts.ps1` içinde sabit IP adresi ve uzaktan komut çalıştırma mantığı bulunduğundan, bu dosya yalnızca izole laboratuvar kullanımı için değerlendirilmelidir.

## Etik Kullanım

Bu proje:

- Yetkisiz erişim,
- Veri hırsızlığı,
- Kimlik bilgisi toplama,
- Kalıcı erişim sağlama,
- Güvenlik kontrollerini atlatma

amacıyla kullanılamaz.

Yalnızca sistem sahibinin açık izniyle ve önceden belirlenmiş test kapsamı içinde kullanılmalıdır.

## Katkıda Bulunma

Güvenli katkılar aşağıdaki konulara odaklanmalıdır:

- Tespit kuralları
- Sigma veya YARA kuralları
- PowerShell olay günlükleri
- USB HID savunması
- Olay müdahalesi
- Görev Zamanlayıcı denetimi
- Güvenli laboratuvar kurulumu
- EDR ve SIEM entegrasyonu
- Gizleme, yetkisiz kalıcılık veya saldırı kapasitesini arttırma

> **Laboratuvar yapılandırması:**  
> Aşağıdaki IP adresi ve port yalnızca örnek değerlerdir:
>
> ```powershell
> System.Net.Sockets.TCPClient('192.168.0.22',443)
> ```
>
> Yetkili ve izole laboratuvar ortamında test yapıyorsanız, bu değerleri yalnızca test bağlantısını kabul etmek üzere yapılandırılmış laboratuvar sunucusunun IP adresi ve portuyla değiştirin.
>
> Gerçek sistemlere, üçüncü taraflara veya üretim ağlarına ait IP adreslerini kullanmayın. Bu bileşen uzak uçtan alınan verileri PowerShell komutu olarak işleyebildiğinden, yalnızca geçici ve izole test ortamlarında çalıştırılmalıdır.


## Lisans

Bu proje yalnızca eğitim ve yetkili güvenlik araştırması amacıyla sunulmaktadır. Kullanıcı, yazılımı kullanmadan önce ilgili sistemler üzerinde gerekli izinlere sahip olduğunu kabul eder.
