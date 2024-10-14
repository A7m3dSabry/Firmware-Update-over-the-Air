import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.zip.CRC32;

public class Main {
    private static final String SERVER_ADDRESS = "localhost";
    private static final int SERVER_PORT = 8000;

    public static void main(String[] args) {
        try (Socket socket = new Socket(SERVER_ADDRESS, SERVER_PORT);
             InputStream inputStream = socket.getInputStream();
             OutputStream outputStream = socket.getOutputStream()) {

            // Test getting the latest version
            requestLatestVersion(outputStream, inputStream);

            // Test getting the image size (requesting file size)
            requestImageSize(outputStream, inputStream);
            // Test getting image data (example: requesting 1000 bytes starting from counter 0)
            requestImageData(outputStream, inputStream, 1000, 0);


        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void requestLatestVersion(OutputStream outputStream, InputStream inputStream) throws IOException {
        byte[] request = new byte[0];  // Empty request
        send(outputStream, (byte) 0x01, request);

        byte[] responseHeader = new byte[3]; // 1 byte header + 2 bytes for size
        inputStream.read(responseHeader);

        int size = ByteBuffer.wrap(responseHeader, 1, 2).getShort() & 0xFFFF;
        byte[] response = new byte[size];
        inputStream.read(response);

        byte[] fullResponse = new byte[responseHeader.length + response.length];
        System.arraycopy(responseHeader, 0, fullResponse, 0, responseHeader.length);
        System.arraycopy(response, 0, fullResponse, responseHeader.length, response.length);

        if (fullResponse[0] == (byte) 0x81) {
            if (validateCRC(fullResponse)) {
                System.out.println("Latest Version: " + String.format("%d.%d.%d", response[0], response[1], response[2]));
            } else {
                System.out.println("CRC validation failed for version response.");
            }
        } else {
            System.out.println("Error retrieving version.");
        }
    }

    private static void requestImageData(OutputStream outputStream, InputStream inputStream, int buffSize, int counter) throws IOException {
        byte[] sizeBuffer = ByteBuffer.allocate(6).putShort((short) buffSize).putInt(counter).array();
        byte[] request = new byte[0];  // Empty request
        send(outputStream, (byte) 0x03, sizeBuffer);

        byte[] responseHeader = new byte[3]; // 1 byte header + 2 bytes for size
        inputStream.read(responseHeader);

        int size = (ByteBuffer.wrap(responseHeader, 1, 2).getShort() & 0xFFFF );
        byte[] response = new byte[size];
        int bytesRead = inputStream.read(response);

        byte[] fullResponse = new byte[responseHeader.length + response.length];
        System.arraycopy(responseHeader, 0, fullResponse, 0, responseHeader.length);
        System.arraycopy(response, 0, fullResponse, responseHeader.length, bytesRead);

        if (bytesRead > 0 && fullResponse[0] == (byte) 0x83) {
            if (validateCRC(fullResponse)) {
                int newCounter = ByteBuffer.wrap(response, 0, 4).getInt();//ByteBuffer.wrap(fullResponse, 1, 4).getInt();
                System.out.println("Received Image Data, starting from counter: " + newCounter);
                // Handle the image data in fullResponse[5...]
            } else {
                System.out.println("CRC validation failed for image data response.");
            }
        } else {
            System.out.println("Error retrieving image data.");
        }
    }

    private static void requestImageSize(OutputStream outputStream, InputStream inputStream) throws IOException {
        byte[] request = new byte[0];  // Empty request
        send(outputStream, (byte) 0x02, request);

        byte[] responseHeader = new byte[3]; // 1 byte header + 2 bytes for size
        inputStream.read(responseHeader);

        int size = ByteBuffer.wrap(responseHeader, 1, 2).getShort() & 0xFFFF;
        byte[] response = new byte[size];
        inputStream.read(response);

        byte[] fullResponse = new byte[responseHeader.length + response.length];
        System.arraycopy(responseHeader, 0, fullResponse, 0, responseHeader.length);
        System.arraycopy(response, 0, fullResponse, responseHeader.length, response.length);

        if (fullResponse[0] == (byte) 0x82) {
            if (validateCRC(fullResponse)) {
                int fileSize = ByteBuffer.wrap(response, 0, 4).getInt();
                System.out.println("Received Image Size: " + fileSize + " bytes");
            } else {
                System.out.println("CRC validation failed for image size response.");
            }
        } else {
            System.out.println("Error retrieving image size.");
        }
    }

    private static void send(OutputStream outputStream, byte header, byte[] data) throws IOException {
        // Calculate the remaining length (data length + CRC byte)
        byte[] remainingLengthBytes = ByteBuffer.allocate(2).putShort((short) (data.length + 1)).array();

        // Create a new byte array that includes the header, length, data, and CRC
        byte[] packet = new byte[1 + 2 + data.length + 1]; // header + size (2 bytes) + data + CRC
        packet[0] = header; // Set the header byte
        System.arraycopy(remainingLengthBytes, 0, packet, 1, 2); // Set the remaining length (size)
        System.arraycopy(data, 0, packet, 3, data.length); // Set the data

        byte crc = calculateCRC(packet, 0, packet.length - 1); // Calculate CRC for the whole packet (including header, length, data)
        packet[packet.length - 1] = crc; // Set the CRC byte

        outputStream.write(packet); // Send the packet
    }

    // CRC validation method (validate the entire packet including header, length, data, and CRC)
    private static boolean validateCRC(byte[] fullPacket) {
        byte expectedCRC = fullPacket[fullPacket.length - 1];
        byte calculatedCRC = calculateCRC(fullPacket, 0, fullPacket.length - 1);
        return expectedCRC == calculatedCRC;
    }

    // Calculate CRC for a given byte array
    private static byte calculateCRC(byte[] data, int start, int length) {
        byte crc = 0;
        for (int i = start; i < start + length; i++) {
            crc+=data[i];
        }
//        CRC32 crc = new CRC32();
//        crc.update(data, start, length);
        return (byte) (0xFF - crc); // Return only the least significant byte
    }
}
