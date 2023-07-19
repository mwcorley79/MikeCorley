namespace viceroy
{
    public sealed class RDTMS_Settings
    {
        public string ConnectionString { get; set; }
        public int TransmitInterval { get; set; }
        public int HVACPin { get; set; }
        public int LEDPin { get; set; }
        public string DeviceId { get; set; }
        public int LCDMaxLines { get; set; }
        public int LCDLineLen { get; set; }
    }
}
