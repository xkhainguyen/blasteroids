import struct

def read_wav_header(filename: str) -> None:
    with open(filename, 'rb') as file:
        # Read the main RIFF header
        riff = file.read(4).decode('utf-8')
        size = struct.unpack('<I', file.read(4))[0]
        wave = file.read(4).decode('utf-8')

        # Find the format chunk (skip non-fmt chunks like JUNK)
        chunk_id = ''
        while chunk_id != 'fmt ':
            chunk_id = file.read(4).decode('utf-8')
            chunk_size = struct.unpack('<I', file.read(4))[0]
            if chunk_id != 'fmt ':
                file.seek(chunk_size, 1)  # Skip the current chunk

        # Read the format chunk
        audio_format, num_channels = struct.unpack('<HH', file.read(4))
        sample_rate = struct.unpack('<I', file.read(4))[0]
        byte_rate = struct.unpack('<I', file.read(4))[0]
        block_align, bits_per_sample = struct.unpack('<HH', file.read(4))

        print(f"RIFF header: {riff}")
        print(f"Size: {size}")
        print(f"WAVE header: {wave}")
        print(f"fmt chunk: {chunk_id}")
        print(f"fmt chunk size: {chunk_size}")
        print(f"Audio Format: {audio_format}")
        print(f"Number of Channels: {num_channels}")
        print(f"Sample Rate: {sample_rate}")
        print(f"Byte Rate: {byte_rate}")
        print(f"Block Align: {block_align}")
        print(f"Bits per Sample: {bits_per_sample}")


# Replace 'path_to_file.wav' with the path to your WAV file
read_wav_header('explosion.wav')