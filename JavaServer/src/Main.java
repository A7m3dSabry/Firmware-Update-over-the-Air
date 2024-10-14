import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;




// private static final String FOLDER = System.getenv("IMAGES_DIR");//
public class Main {

    public static final byte PACKET_HEADER_GET_VERSION = (byte) 0x01;
    public static final byte PACKET_HEADER_GET_FILE_SIZE = (byte) 0x02;
    public static final byte PACKET_HEADER_DOWNLOAD_IMAGE_PART = (byte) 0x03;

    public static final byte PACKET_HEADER_GET_VERSION_RESPONSE = (byte) 0x81;
    public static final byte PACKET_HEADER_GET_FILE_SIZE_RESPONSE = (byte) 0x82;
    public static final byte PACKET_HEADER_DOWNLOAD_IMAGE_PART_RESPONSE = (byte) 0x83;


    // for future work with docker
    // private static final int PORT = Integer.parseInt(System.getenv("PORT"));

    private static final int PORT = 8000;
    private static final String FOLDER = "TEXT_FILES_PATH";

    public static void main(String[] args) {
        ExecutorService executor = Executors.newFixedThreadPool(10); // Thread pool for handling clients

        try (ServerSocket serverSocket = new ServerSocket(PORT)) {
            System.out.println("Server listening on port " + PORT);
            while (true) {
                Socket clientSocket = serverSocket.accept();
                executor.submit(() -> handleClient(clientSocket));
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void handleClient(Socket clientSocket) {
        System.out.println("Client connected");
        try (InputStream inputStream = clientSocket.getInputStream();
             OutputStream outputStream = clientSocket.getOutputStream()) {

            while (true) {
                // Read the header byte and remaining length (2 bytes)
                byte[] headerBuffer = new byte[3]; // 1 byte header + 2 bytes for remaining length
                int bytesRead = inputStream.read(headerBuffer);
                if (bytesRead != 3) {
                    continue;  // if we haven't read a full header, skip
                }

                byte header = headerBuffer[0];
                int remainingLength = ByteBuffer.wrap(headerBuffer, 1, 2).getShort() & 0xFFFF;

                // Read the rest of the packet (data + CRC byte)
                byte[] packetData = new byte[remainingLength];
                inputStream.read(packetData);

                // Combine the header and packetData to form the entire packet (including CRC)
                byte[] fullPacket = new byte[3 + remainingLength];
                System.arraycopy(headerBuffer, 0, fullPacket, 0, 3);
                System.arraycopy(packetData, 0, fullPacket, 3, remainingLength);

                // Validate the CRC for the entire packet (header, length, data, and CRC)
                if (!validateCRC(fullPacket)) {
                    sendError(outputStream, (byte) 0xFF); // Invalid CRC
                    continue;
                }

                // Process the packet based on the header
                if (header == PACKET_HEADER_GET_VERSION) {
                    // Request for latest version
                    try {
                        byte[] versionResponse = getLatestVersion();
                        send(outputStream, (byte) PACKET_HEADER_GET_VERSION_RESPONSE, versionResponse);
                    } catch (Exception e) {
                        sendError(outputStream, (byte) PACKET_HEADER_GET_VERSION); // Error for getLatestVersion
                    }
                } else if (header == PACKET_HEADER_GET_FILE_SIZE) {
                    // Request for image size
                    try {
                        byte[] imageSize = getLatestImageSize();
                        send(outputStream, (byte) PACKET_HEADER_GET_FILE_SIZE_RESPONSE, imageSize);
                    } catch (Exception e) {
                        sendError(outputStream, (byte) PACKET_HEADER_GET_FILE_SIZE); // Error for getImageSize
                    }
                } else if (header == PACKET_HEADER_DOWNLOAD_IMAGE_PART) {
                    // Request for image data
                    try {
                        byte[] data = getLatestImageData(packetData);
                        send(outputStream, (byte) PACKET_HEADER_DOWNLOAD_IMAGE_PART_RESPONSE, data);
                    } catch (Exception e) {
                        sendError(outputStream, (byte) PACKET_HEADER_DOWNLOAD_IMAGE_PART); // Error for getImageData
                    }
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    // Get the latest modified .txt file
    private static File getLatestTextFile(String folderPath) {
        File folder = new File(folderPath);
        File latestFile = null;

        for (File file : folder.listFiles()) {
            if (file.getName().endsWith(".txt") && (latestFile == null || file.lastModified() > latestFile.lastModified())) {
                latestFile = file;
            }
        }

        return latestFile;
    }

    // Get the latest version as a byte array from the latest .txt file
    private static byte[] getLatestVersion() throws IOException {
        File latestFile = getLatestTextFile(FOLDER);

        if (latestFile != null) {
            try (BufferedReader reader = new BufferedReader(new FileReader(latestFile))) {
                String versionLine = reader.readLine();
                String version = versionLine.split("=")[1].trim();

                // Convert version string to byte array
                String[] versionNumbers = version.split("\\.");
                byte[] versionBytes = new byte[versionNumbers.length];
                for (int i = 0; i < versionNumbers.length; i++) {
                    versionBytes[i] = (byte) Integer.parseInt(versionNumbers[i]);
                }
                return versionBytes;
            }
        }

        throw new IOException("No version file found");
    }

    // Get the latest path from the latest .txt file
    private static String getLatestPath() throws IOException {
        File latestFile = getLatestTextFile(FOLDER);

        if (latestFile != null) {
            try (BufferedReader reader = new BufferedReader(new FileReader(latestFile))) {
                reader.readLine(); // Skip version line
                String pathLine = reader.readLine();
                return pathLine.split("=")[1].trim();
            }
        }

        throw new IOException("No path file found");
    }

    // Get the latest image size based on the path from the latest .txt file
    private static byte[] getLatestImageSize() throws IOException {
        String imagePath = getLatestPath();
        File imageFile = new File(imagePath);
        if (imageFile.exists()) {
            byte[] sizeBytes = ByteBuffer.allocate(4).putInt((int) imageFile.length()).array();
            return sizeBytes;
        } else {
            return ByteBuffer.allocate(4).putInt(0).array();
        }
    }

    // Get image data based on the path from the latest .txt file
    private static byte[] getLatestImageData(byte[] packetData) throws IOException {
        int counter = ByteBuffer.wrap(packetData, 2, 4).getInt();
        int dataSize = ByteBuffer.wrap(packetData, 0, 2).getShort() - 8; // Adjust size to account for header, counter size, and CRC

        byte[] buffer = new byte[dataSize];
        String imagePath = getLatestPath();

        File imageFile = new File(imagePath);
        if (imageFile.exists()) {
            try (FileInputStream fis = new FileInputStream(imageFile)) {
                fis.skip(counter);
                int bytesRead = fis.read(buffer);
                byte[] bytesReadArray = ByteBuffer.allocate(4).putInt(bytesRead).array();
                byte[] finalBuffer = new byte[bytesRead + 4];
                System.arraycopy(bytesReadArray, 0, finalBuffer, 0, 4);
                System.arraycopy(buffer, 0, finalBuffer, 4, bytesRead);
                return finalBuffer;
            }
        }

        throw new IOException("No image file found");
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
            crc += data[i];
        }
        return (byte) (0xFF - crc); // Return only the least significant byte
    }

    // Send method for sending data packets
    private static void send(OutputStream outputStream, byte header, byte[] data) throws IOException {
        // Include size in 2 bytes after header, and CRC byte at the end
        byte[] sizeBytes = ByteBuffer.allocate(2).putShort((short) (data.length + 1)).array(); // Data length + 1 byte for CRC
        byte[] response = new byte[1 + 2 + data.length + 1]; // header + size (2 bytes) + data + CRC

        response[0] = header;
        System.arraycopy(sizeBytes, 0, response, 1, 2);     // copy data length
        System.arraycopy(data, 0, response, 3, data.length); // copy actual data
        response[response.length - 1] = calculateCRC(response, 0, response.length - 1); // Add CRC at the end
        outputStream.write(response);
    }

    // Send error response
    private static void sendError(OutputStream outputStream, byte errorNumber) throws IOException {
        // Send an error packet (Header byte 0xF0, error number)
        byte[] errorResponse = new byte[]{(byte) 0xF0, errorNumber};
        send(outputStream, (byte) 0xF0, errorResponse);
    }
}
