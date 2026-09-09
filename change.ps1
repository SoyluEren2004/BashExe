# Mevcut dil listesini al
$languageList = Get-WinUserLanguageList

# en-US dilini bul
$english = $languageList | Where-Object {
    $_.LanguageTag -eq "en-US"
}

# en-US dili yoksa oluştur
if ($null -eq $english) {
    $english = (New-WinUserLanguageList "en-US")[0]
    $languageList += $english
}

# İngilizce klavye düzenini temizle ve English US ekle
$english.InputMethodTips.Clear()
$english.InputMethodTips.Add("0409:00000409")

# İngilizceyi listenin ilk sırasına al,
# diğer dilleri koru
$otherLanguages = $languageList | Where-Object {
    $_.LanguageTag -ne "en-US"
}

$newLanguageList = @($english) + @($otherLanguages)

# Dil ve klavye listesini uygula
Set-WinUserLanguageList -LanguageList $newLanguageList -Force

# İngilizce Q'yu varsayılan yap
Set-WinDefaultInputMethodOverride -InputTip "0409:00000409"
