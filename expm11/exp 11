import java.math.BigInteger;
import java.security.SecureRandom;

public class DSAExample {

    public static void main(String[] args) {
        // Step 1: Generate large prime numbers p and q
        BigInteger p = new BigInteger("11257345836008975928570625102677103915741561246484170758998679349011425228759439087801130946985382059424100697352207359961155389342236926022835139889050687");
        BigInteger q = new BigInteger("654810019837599169203394123926748027386695598659");

        // Step 2: Compute g, a generator of a multiplicative group modulo p
        BigInteger g = computeGenerator(p, q);

        // Step 3: Generate private key x
        BigInteger x = generatePrivateKey(q);

        // Step 4: Compute public key y
        BigInteger y = g.modPow(x, p);

        // Step 5: Sign a message using DSA
        BigInteger[] signature = signMessage(p, q, g, x, "Hello, World!");

        // Step 6: Verify the signature
        boolean verified = verifySignature(p, q, g, y, "Hello, World!", signature);

        // Step 7: Output the results
        System.out.println("Message: Hello, World!");
        System.out.println("Signature (r, s): (" + signature[0] + ", " + signature[1] + ")");
        System.out.println("Signature verified: " + verified);
    }

    // Method to compute a generator g of a multiplicative group modulo p
    public static BigInteger computeGenerator(BigInteger p, BigInteger q) {
        BigInteger g = BigInteger.ONE; // Simplified; in real applications, g would be calculated differently
        return g;
    }

    // Method to generate a private key x
    public static BigInteger generatePrivateKey(BigInteger q) {
        SecureRandom random = new SecureRandom();
        BigInteger x;
        do {
            x = new BigInteger(q.bitLength(), random);
        } while (x.compareTo(BigInteger.ZERO) <= 0 || x.compareTo(q) >= 0);
        return x;
    }

    // Method to sign a message using DSA
    public static BigInteger[] signMessage(BigInteger p, BigInteger q, BigInteger g, BigInteger x, String message) {
        SecureRandom random = new SecureRandom();
        BigInteger[] signature = new BigInteger[2];

        BigInteger m = new BigInteger(message.getBytes());

        BigInteger k;
        do {
            k = new BigInteger(q.bitLength(), random);
        } while (k.compareTo(BigInteger.ZERO) <= 0 || k.compareTo(q) >= 0);

        BigInteger r = g.modPow(k, p).mod(q);
        BigInteger kInv = k.modInverse(q);
        BigInteger s = kInv.multiply(m.add(x.multiply(r))).mod(q);

        signature[0] = r;
        signature[1] = s;

        return signature;
    }

    // Method to verify a signature
    public static boolean verifySignature(BigInteger p, BigInteger q, BigInteger g, BigInteger y, String message, BigInteger[] signature) {
        BigInteger r = signature[0];
        BigInteger s = signature[1];

        if (r.compareTo(BigInteger.ZERO) <= 0 || r.compareTo(q) >= 0 ||
            s.compareTo(BigInteger.ZERO) <= 0 || s.compareTo(q) >= 0) {
            return false;
        }

        BigInteger m = new BigInteger(message.getBytes());
        BigInteger w = s.modInverse(q);
        BigInteger u1 = m.multiply(w).mod(q);
        BigInteger u2 = r.multiply(w).mod(q);

        BigInteger v1 = g.modPow(u1, p);
        BigInteger v2 = y.modPow(u2, p);
        BigInteger v = v1.multiply(v2).mod(p).mod(q);

        return v.equals(r);
    }
}
