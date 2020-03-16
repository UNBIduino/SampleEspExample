package duinoCypher

import javax.crypto.Cipher
import javax.crypto.spec.IvParameterSpec
import javax.crypto.spec.SecretKeySpec


fun main() {
    val ivbyte= hexStringToByteArray("9ad03002000000009ad0300200000000")
    val cypher= hexStringToByteArray("e291b05aee8f75b27a3669d9266e46ce");
//    val key="0123456789010123".toByteArray();
    val key= hexStringToByteArray("30313233343536373839303130313233")
//    val msg= byteArrayOf(72,101,108,108,111,11,11,11,11,11,11,11,11,11,11,11)
    val msg= "Hello World!!!!!".toByteArray()
    val iv = IvParameterSpec(ivbyte)
    val skeySpec = SecretKeySpec(key,"AES")
    val cipher = Cipher.getInstance("AES/CBC/PKCS5PADDING")
    cipher.init(Cipher.ENCRYPT_MODE, skeySpec, iv)
    val encrypted = cipher.doFinal(msg)
    val encrypted_hex= encrypted.toHexString()
    println(encrypted_hex)

    //////Decryption Part//////////
    val dcipher = Cipher.getInstance("AES/CBC/PKCS5PADDING")
    dcipher.init(Cipher.DECRYPT_MODE, skeySpec, iv)
    val decrypted=dcipher.doFinal(encrypted)
    println(String(decrypted))

}

fun hexStringToByteArray(s: String): ByteArray {
    val len = s.length
    val data = ByteArray(len / 2)
    var i = 0
    while (i < len) {
        data[i / 2] = ((Character.digit(s[i], 16) shl 4) + Character.digit(s[i + 1], 16)).toByte()
        i += 2
    }
    return data
}

fun ByteArray.toHexString() = asUByteArray().joinToString("") { it.toString(16).padStart(2, '0') }