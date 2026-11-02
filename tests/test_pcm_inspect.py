import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).parent / "tools"))

from pcm_inspect import analyze_pcm, decode_pcm16le


class PcmInspectTests(unittest.TestCase):
    def test_decode_signed_little_endian_samples(self):
        self.assertEqual(decode_pcm16le(b"\x01\x00\xff\xff"), [1, -1])

    def test_reject_incomplete_sample(self):
        with self.assertRaises(ValueError):
            decode_pcm16le(b"\x01")

    def test_calculate_audio_metrics(self):
        result = analyze_pcm([1000, -1000, 0], 16000)

        self.assertEqual(result["sample_count"], 3)
        self.assertEqual(result["peak"], 1000)
        self.assertEqual(result["mean"], 0)
        self.assertEqual(result["clipped_samples"], 0)
        self.assertAlmostEqual(result["rms"], (2000000 / 3) ** 0.5)

    def test_reject_empty_audio(self):
        with self.assertRaises(ValueError):
            analyze_pcm([], 16000)

    def test_reject_invalid_sample_rate(self):
        with self.assertRaises(ValueError):
            analyze_pcm([1, 2], 0)


if __name__ == "__main__":
    unittest.main()
