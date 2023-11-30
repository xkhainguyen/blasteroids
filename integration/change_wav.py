import struct

def clean_wav_file(input_filename: str, output_filename: str) -> None:
    with open(input_filename, 'rb') as infile:
        riff = infile.read(4)
        if riff != b'RIFF':
            raise ValueError('Not a valid RIFF file')

        size = struct.unpack('<I', infile.read(4))[0]
        wave = infile.read(4)
        if wave != b'WAVE':
            raise ValueError('Not a valid WAVE file')

        # Prepare to write to the new file
        with open(output_filename, 'wb') as outfile:
            outfile.write(riff)
            outfile.write(struct.pack('<I', size))
            outfile.write(wave)

            # Process chunks
            while infile.tell() < size + 8:
                chunk_id = infile.read(4)
                chunk_size = struct.unpack('<I', infile.read(4))[0]

                # If it's a 'fmt ' or 'data' chunk, write it to the new file
                if chunk_id in [b'fmt ', b'data']:
                    outfile.write(chunk_id)
                    outfile.write(struct.pack('<I', chunk_size))
                    outfile.write(infile.read(chunk_size))
                else:
                    # Otherwise, skip this chunk
                    infile.seek(chunk_size, 1)


clean_wav_file('blaster.wav', 'blaster2.wav')
print('Saved new wav file')